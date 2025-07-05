//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_CHECKED_OPS_INL
#define ARBITRARYUNSIGNEDINT_CHECKED_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAdd(const ArbitraryUnsignedInt& other) const {
    auto result = *this + other;
    if (result > *this || result > other) {
        return std::nullopt;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedSub(const ArbitraryUnsignedInt& other) const {
    auto result = *this - other;
    if (*this < other) {
        return std::nullopt;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedMul(const ArbitraryUnsignedInt& other) const {
    ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType> widened_result = WideningMul(*this, other);

    // Check if the upper BitSize bits are zero
    bool overflow = false;
    for (size_t i = BitSize; i < BitSize * 2; ++i) {
        if (widened_result.GetBit(i)) {
            overflow = true;
            break;
        }
    }

    if (overflow) {
        return std::nullopt;
    }
    else {
        // Truncate the result back to BitSize
        ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
        result.GetStorage().CopyBitsFrom(widened_result.GetStorage(), widened_result.GetBitOffset(), BitSize, result.GetBitOffset());
        return result;
    }
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedDiv(const ArbitraryUnsignedInt& other) const {
    if (other.IsZero()) {
        return std::nullopt; // Division by zero
    }
    return DivRem(other).first;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedRem(const ArbitraryUnsignedInt& other) const {
    if (other.IsZero()) {
        return std::nullopt; // Division by zero
    }
    return DivRem(other).second;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPow(const ArbitraryUnsignedInt& exp) const {
    ArbitraryUnsignedInt base = *this;
    ArbitraryUnsignedInt result(1);
    ArbitraryUnsignedInt exponent = exp;

    if (exp.IsZero()) {
        return ArbitraryUnsignedInt(1);
    }
    if (base.IsZero()) {
        return ArbitraryUnsignedInt(0);
    }

    while (!exponent.IsZero()) {
        if (exponent.GetBit(0)) {
            // If exponent is odd
            std::optional<ArbitraryUnsignedInt> checked_mul_result = result.CheckedMul(base);
            if (!checked_mul_result) {
                return std::nullopt; // Overflow
            }
            result = *checked_mul_result;
        }
        std::optional<ArbitraryUnsignedInt> checked_base_mul_result = base.CheckedMul(base);
        if (!checked_base_mul_result) {
            return std::nullopt; // Overflow
        }
        base = *checked_base_mul_result;
        exponent >>= 1;
    }
    return result;
}

#endif //ARBITRARYUNSIGNEDINT_CHECKED_OPS_INL
