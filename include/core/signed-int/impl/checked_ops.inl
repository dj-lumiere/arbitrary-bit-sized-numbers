//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_CHECKED_OPS_INL
#define ARBITRARYSIGNEDINT_CHECKED_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAdd(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedAdd(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAdd(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedSub(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedSub(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedSub(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedMul(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedMul(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedMul(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedDiv(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedDiv(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedDiv(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedRem(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedRem(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedRem(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNeg() const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedNeg() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNeg() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAbs() const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedAbs() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAbs() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPow(const ArbitrarySignedInt& exp) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedPow(const ArbitrarySignedInt& exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPow(const ArbitrarySignedInt& exp) not implemented.");
}

#endif //ARBITRARYSIGNEDINT_CHECKED_OPS_INL
