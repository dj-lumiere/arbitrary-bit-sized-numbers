//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_BYTE_CONVERSION_INL
#define ARBITRARYUNSIGNEDINT_BYTE_CONVERSION_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToBeBytes() const {
    std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> result;
    constexpr size_t storageSize = ((BitSize + BitOffset + 7) >> 3);

    // Copy bytes from storage and reverse for big-endian
    for (size_t i = 0; i < storageSize; ++i) {
        result[i] = storage_.data_[storageSize - 1 - i];
    }

    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToLeBytes() const {
    std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> result;
    constexpr size_t storageSize = ((BitSize + BitOffset + 7) >> 3);

    // Copy bytes directly for little-endian (storage is already little-endian)
    for (size_t i = 0; i < storageSize; ++i) {
        result[i] = storage_.data_[i];
    }

    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToNeBytes() const {
    // Native endian - check system endianness
    if constexpr (std::endian::native == std::endian::little) {
        return ToLeBytes();
    }
    else {
        return ToBeBytes();
    }
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    ArbitraryUnsignedInt result;
    constexpr size_t storageSize = ((BitSize + BitOffset + 7) >> 3);

    // Convert from big-endian by reversing byte order
    for (size_t i = 0; i < storageSize; ++i) {
        result.storage_.data_[i] = bytes[storageSize - 1 - i];
    }

    result.Normalize();
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    ArbitraryUnsignedInt result;
    constexpr size_t storageSize = ((BitSize + BitOffset + 7) >> 3);

    // Copy bytes directly from little-endian
    for (size_t i = 0; i < storageSize; ++i) {
        result.storage_.data_[i] = bytes[i];
    }

    result.Normalize();
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // Native endian - check system endianness
    if constexpr (std::endian::native == std::endian::little) {
        return FromLeBytes(bytes);
    }
    else {
        return FromBeBytes(bytes);
    }
}

#endif //ARBITRARYUNSIGNEDINT_BYTE_CONVERSION_INL
