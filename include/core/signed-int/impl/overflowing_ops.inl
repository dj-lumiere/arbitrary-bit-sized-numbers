//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_OVERFLOWING_OPS_INL
#define ARBITRARYSIGNEDINT_OVERFLOWING_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingAdd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingAdd(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingAdd(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingSub(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingSub(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingSub(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingMul(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingMul(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingMul(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingDiv(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingDiv(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingDiv(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingRem(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingRem(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingRem(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingNeg() {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingNeg() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingNeg() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingAbs() {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingAbs() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingAbs() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingPow(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& exp) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingPow(const ArbitrarySignedInt& exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingPow(const ArbitrarySignedInt& exp) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingShl(size_t shift) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingShl(size_t shift) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShl(size_t shift) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingShr(size_t shift) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingShr(size_t shift) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShr(size_t shift) not implemented.");
}

#endif //ARBITRARYSIGNEDINT_OVERFLOWING_OPS_INL
