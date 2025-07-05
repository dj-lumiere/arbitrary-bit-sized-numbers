//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_ARITHMETIC_INL
#define ARBITRARYUNSIGNEDINT_ARITHMETIC_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator+(const ArbitraryUnsignedInt& other) {
    storage_.OffsetAdd(other.GetStorage(), BitOffset, BitSize, other.GetBitOffset());
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator-(const ArbitraryUnsignedInt& other) {
    storage_.OffsetSub(other.GetStorage(), BitOffset, BitSize, other.GetBitOffset());
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator*(const ArbitraryUnsignedInt& other) {
    ArbitraryUnsignedInt result;
    ArbitraryUnsignedInt multiplicand = *this;
    ArbitraryUnsignedInt multiplier = other;

    // Handle zero cases
    if (multiplicand.IsZero() || multiplier.IsZero()) {
        return result;
    }

    size_t bitShiftCount = BitSize;
    // Standard binary multiplication algorithm
    while (bitShiftCount) {
        if (multiplier.GetBit(0)) {
            // If lowest bit is 1
            result += multiplicand;
        }
        multiplicand <<= 1; // Shift multiplicand left
        multiplier >>= 1; // Shift multiplier right
        bitShiftCount -= 1;
    }

    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator/(const ArbitraryUnsignedInt& other) {
    // Division by zero check
    if (other.IsZero()) {
        throw std::runtime_error("Division by zero");
    }

    ArbitraryUnsignedInt quotient;

    // Handle zero dividend
    if (this->IsZero()) {
        return quotient;
    }

    // Handle division by 1 (all zeros except LSB)
    ArbitraryUnsignedInt one;
    one.storage_.ClearAllBits();
    one.SetBit(0);
    if (other == one) {
        return *this;
    }

    // Long division algorithm using bit operations
    ArbitraryUnsignedInt dividend = *this;
    ArbitraryUnsignedInt divisor = other;

    // Find the position of the most significant bit in divisor
    size_t divisor_msb = 0;
    for (size_t i = BitSize; i > 0; --i) {
        if (divisor.GetBit(i - 1)) {
            divisor_msb = i - 1;
            break;
        }
    }

    // Find the position of the most significant bit in dividend
    size_t dividend_msb = 0;
    for (size_t i = BitSize; i > 0; --i) {
        if (dividend.GetBit(i - 1)) {
            dividend_msb = i - 1;
            break;
        }
    }

    if (dividend_msb < divisor_msb) {
        return quotient; // Result is 0
    }

    // Shift divisor to align with dividend's MSB
    size_t shift = dividend_msb - divisor_msb;
    divisor.storage_.ShiftLeft(shift);

    for (size_t i = 0; i <= shift; ++i) {
        // Compare dividend with shifted divisor
        // If dividend is greater than or equal to divisor
        if (dividend >= divisor) {
            // Subtract divisor from dividend using OffsetSubWithBorrow
            auto sub_result = dividend.GetStorage().OffsetSubWithBorrow(divisor.GetStorage(), divisor.GetBitOffset(), BitSize, dividend.GetBitOffset(), false);
            dividend.GetStorage() = sub_result.first;

            // Set corresponding bit in quotient
            quotient.SetBit(shift - i);
        }

        // Shift divisor right for next iteration
        if (i < shift) {
            divisor.storage_.ShiftRight(1);
        }
    }

    return quotient;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator%(const ArbitraryUnsignedInt& other) {
    // Division by zero check
    if (other.IsZero()) {
        throw std::runtime_error("Division by zero");
    }

    // Handle zero dividend
    if (this->IsZero()) {
        ArbitraryUnsignedInt result;
        return result;
    }

    // Handle modulo by 1
    ArbitraryUnsignedInt one;
    one.storage_.ClearAllBits();
    one.SetBit(0);
    if (other == one) {
        ArbitraryUnsignedInt result;
        result.storage_.ClearAllBits();
        return result;
    }

    // Use the same long division algorithm as division,
    // but return the remainder instead of quotient
    ArbitraryUnsignedInt remainder = *this;
    ArbitraryUnsignedInt divisor = other;

    // Find MSB positions
    size_t divisor_msb = 0;
    for (size_t i = BitSize; i > 0; --i) {
        if (divisor.GetBit(i - 1)) {
            divisor_msb = i - 1;
            break;
        }
    }

    size_t remainder_msb = 0;
    for (size_t i = BitSize; i > 0; --i) {
        if (remainder.GetBit(i - 1)) {
            remainder_msb = i - 1;
            break;
        }
    }

    if (remainder_msb < divisor_msb) {
        return remainder;
    }

    // Shift divisor to align with remainder's MSB
    size_t shift = remainder_msb - divisor_msb;
    divisor.storage_.ShiftLeft(shift);

    for (size_t i = 0; i <= shift; ++i) {
        // Compare remainder with shifted divisor
        if (remainder >= divisor) {
            // Subtract divisor from remainder using OffsetSubWithBorrow
            auto sub_result = remainder.GetStorage().OffsetSubWithBorrow(divisor.GetStorage(), divisor.GetBitOffset(), BitSize, remainder.GetBitOffset(), false);
            remainder.GetStorage() = sub_result.first;
        }

        // Shift divisor right for next iteration
        if (i < shift) {
            divisor.storage_.ShiftRight(1);
        }
    }

    return remainder;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator+=(const ArbitraryUnsignedInt& other) {
    *this = *this + other;
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator-=(const ArbitraryUnsignedInt& other) {
    *this = *this - other;
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator*=(const ArbitraryUnsignedInt& other) {
    *this = *this * other;
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator/=(const ArbitraryUnsignedInt& other) {
    *this = *this / other;
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator%=(const ArbitraryUnsignedInt& other) {
    *this = *this % other;
    return *this;
}

#endif //ARBITRARYUNSIGNEDINT_ARITHMETIC_INL
