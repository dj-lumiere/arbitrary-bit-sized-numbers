//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_SATURATING_OPS_INL
#define ARBITRARYSIGNEDINT_SATURATING_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAdd(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAdd(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAdd(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingSub(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingSub(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingSub(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAbs() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAbs() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAbs() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingNeg() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingNeg() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingNeg() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitrarySignedInt& exp) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitrarySignedInt& exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitrarySignedInt& exp) not implemented.");
}

#endif //ARBITRARYSIGNEDINT_SATURATING_OPS_INL
