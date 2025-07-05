//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_SATURATING_OPS_INL
#define ARBITRARYUNSIGNEDINT_SATURATING_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAdd(const ArbitraryUnsignedInt& other) const {
    auto result = *this + other;
    if (result > *this || result > other) {
        return ArbitraryUnsignedInt::Max();
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingSub(const ArbitraryUnsignedInt& other) const {
    auto result = *this - other;
    if (*this < other) {
        return ArbitraryUnsignedInt::Min();
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitraryUnsignedInt& other) const {
    std::optional<ArbitraryUnsignedInt> checked_mul_result = CheckedMul(other);
    if (checked_mul_result) {
        return *checked_mul_result;
    }
    else {
        return ArbitraryUnsignedInt::Max();
    }
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitraryUnsignedInt& exp) const {
    std::optional<ArbitraryUnsignedInt> checked_pow_result = CheckedPow(exp);
    if (checked_pow_result) {
        return *checked_pow_result;
    }
    else {
        return ArbitraryUnsignedInt::Max();
    }
}

#endif //ARBITRARYUNSIGNEDINT_SATURATING_OPS_INL
