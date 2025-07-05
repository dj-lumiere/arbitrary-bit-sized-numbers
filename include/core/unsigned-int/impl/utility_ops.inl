//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_UTILITY_OPS_INL
#define ARBITRARYUNSIGNEDINT_UTILITY_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> >
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::DivRem(const ArbitraryUnsignedInt& other) const {
    // Division by zero check
    if (other.IsZero()) {
        throw std::runtime_error("Division by zero");
    }

    ArbitraryUnsignedInt quotient;

    // Handle zero dividend
    if (this->IsZero()) {
        return { quotient, ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>() };
    }

    // Handle division by 1 (all zeros except LSB)
    ArbitraryUnsignedInt one;
    one.storage_.ClearAllBits();
    one.SetBit(0);
    if (other == one) {
        return { *this, ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>() };
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
        return { quotient, dividend }; // Result is 0
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

    return { quotient, dividend };
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Pow(const ArbitraryUnsignedInt& exp) const {
    // Implemented by Exponentiation by Squaring
    ArbitraryUnsignedInt result = 1;
    ArbitraryUnsignedInt base = *this;
    while (!exp.IsZero()) {
        if (exp.GetBit(0)) {
            result *= base;
        }
        base *= base;
        exp.storage_.ShiftRight(1);
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Pow(size_t exp) const {
    ArbitraryUnsignedInt result = 1;
    ArbitraryUnsignedInt base = *this;
    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T>
std::optional<T> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TryInto() const {
    // TODO: Implement std::optional<T> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TryInto() const
    throw std::runtime_error("std::optional<T> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TryInto() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNextPowerOfTwo() const {
    // TODO: Implement std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNextPowerOfTwo() const
    throw std::runtime_error("std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNextPowerOfTwo() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPreviousPowerOfTwo() const {
    // TODO: Implement std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPreviousPowerOfTwo() const
    throw std::runtime_error("std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPreviousPowerOfTwo() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::IsPowerOfTwo() const {
    // TODO: Implement bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::IsPowerOfTwo() const
    throw std::runtime_error("bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::IsPowerOfTwo() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> Gcd(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    // This code is based on euclid's algorithm, which states 
    // WLOG, gcd(a, b) = gcd(a % b, b)
    // So, we can just call the recursive function.
    if (a < b) {
        return Gcd(b, a);
    }
    return b.IsZero() ?
               a :
               Gcd(b, a % b);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> Lcm(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    return a * b / Gcd(a, b);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType> WideningMul(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType> result; // Initialize to zero

    // Iterate through each bit of 'b'
    for (size_t i = 0; i < BitSize; ++i) {
        if (b.GetBit(i)) {
            // If the i-th bit of 'b' is set
            bool current_carry = false;
            // Add 'a' shifted left by 'i' positions to the result
            // The source is a.storage_, starting from a.BitOffset, with BitSize bits
            // The destination is result.storage_, starting from result.BitOffset + i
            auto add_result = result.GetStorage().OffsetAddWithCarry(a.GetStorage(), a.GetBitOffset(), BitSize, result.GetBitOffset() + i, current_carry);
            result.GetStorage() = add_result.first;
            current_carry = add_result.second;

            // Propagate remaining carry
            for (size_t k = BitSize; k < BitSize * 2; ++k) {
                size_t result_bit_index = i + k;
                if (result_bit_index < BitSize * 2) {
                    if (current_carry) {
                        bool bit_result = result.GetBit(result_bit_index);
                        bool sum_bit = bit_result ^ current_carry;
                        current_carry = bit_result && current_carry;
                        result.SetBit(result_bit_index, sum_bit);
                    }
                    else {
                        break; // No more carry
                    }
                }
            }
        }
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType> WideningLcm(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    return WideningMul(a, b / Gcd(a, b));
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> CarryingAdd(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry) {
    if (carry) {
        std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> result = a.OverflowingAdd(b);
        std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> result2 = result.first.OverflowingAdd(1);
        return { result2.first, result.second || result2.second };
    }
    return a.OverflowingAdd(b);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> BorrowingSub(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow) {
    if (borrow) {
        std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> result = a.OverflowingSub(b);
        std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> result2 = result.first.OverflowingSub(1);
        return { result2.first, result.second || result2.second };
    }
    return a.OverflowingSub(b);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Normalize() {
    // TODO: Implement void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Normalize()
    return;
}

#endif //ARBITRARYUNSIGNEDINT_UTILITY_OPS_INL
