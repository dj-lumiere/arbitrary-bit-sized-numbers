//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_BYTE_CONVERSION_INL
#define ARBITRARYSIGNEDINT_BYTE_CONVERSION_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToBeBytes() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBeBytes() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToLeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToLeBytes() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToLeBytes() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToNeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToNeBytes() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToNeBytes() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
}

#endif //ARBITRARYSIGNEDINT_BYTE_CONVERSION_INL
