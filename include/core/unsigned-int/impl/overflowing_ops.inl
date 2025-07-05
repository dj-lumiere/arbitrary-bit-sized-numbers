//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_OVERFLOWING_OPS_INL
#define ARBITRARYUNSIGNEDINT_OVERFLOWING_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingAdd(const ArbitraryUnsignedInt& other) const {
    auto result = *this + other;
    if (result > *this || result > other) {
        return { result, true };
    }
    return { result, false };
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingSub(const ArbitraryUnsignedInt& other) const {
    auto result = *this - other;
    if (*this < other) {
        return { result, true };
    }
    return { result, false };
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingMul(const ArbitraryUnsignedInt& other) const {
    ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType> widened_result = WideningMul(*this, other);

    bool overflow = false;
    for (size_t i = BitSize; i < BitSize * 2; ++i) {
        if (widened_result.GetBit(i)) {
            overflow = true;
            break;
        }
    }

    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.GetStorage().CopyBitsFrom(widened_result.GetStorage(), widened_result.GetBitOffset(), BitSize, result.GetBitOffset());
    return { result, overflow };
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingDiv(const ArbitraryUnsignedInt& other) const {
    if (other.IsZero()) {
        throw std::runtime_error("Division by zero"); // Or handle as an overflow, depending on desired behavior
    }
    return { DivRem(other).first, false }; // Division itself doesn't overflow for unsigned ints
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingRem(const ArbitraryUnsignedInt& other) const {
    if (other.IsZero()) {
        throw std::runtime_error("Division by zero"); // Or handle as an overflow
    }
    return { DivRem(other).second, false }; // Remainder itself doesn't overflow for unsigned ints
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingPow(const ArbitraryUnsignedInt& exp) const {
    ArbitraryUnsignedInt base = *this;
    ArbitraryUnsignedInt result(1);
    ArbitraryUnsignedInt exponent = exp;
    bool overflow = false;

    if (exp.IsZero()) {
        return { ArbitraryUnsignedInt(1), false };
    }
    if (base.IsZero()) {
        return { ArbitraryUnsignedInt(0), false };
    }

    while (!exponent.IsZero()) {
        if (exponent.GetBit(0)) {
            // If exponent is odd
            std::pair<ArbitraryUnsignedInt, bool> mul_result = result.OverflowingMul(base);
            result = mul_result.first;
            overflow = overflow || mul_result.second;
        }
        std::pair<ArbitraryUnsignedInt, bool> base_mul_result = base.OverflowingMul(base);
        base = base_mul_result.first;
        overflow = overflow || base_mul_result.second;
        exponent >>= 1;
    }
    return { result, overflow };
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShl(size_t shift) const {
    ArbitraryUnsignedInt result = *this;
    bool overflow = false;
    for (size_t i = BitSize - shift; i < BitSize; ++i) {
        if (result.GetBit(i)) {
            overflow = true;
            break;
        }
    }
    result <<= shift;
    return { result, overflow };
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShr(size_t shift) const {
    ArbitraryUnsignedInt result = *this;
    bool overflow = false; // Right shift doesn't typically overflow for unsigned ints
    result >>= shift;
    return { result, overflow };
}

#endif //ARBITRARYUNSIGNEDINT_OVERFLOWING_OPS_INL
