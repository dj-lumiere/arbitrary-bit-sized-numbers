//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_CONSTRUCTOR_INL
#define ARBITRARYSIGNEDINT_CONSTRUCTOR_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T, typename>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ArbitrarySignedInt(T value) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    storage_.Clear();

    // bit cast the T
    using UnsignedT = std::make_unsigned_t<T>;
    UnsignedT bits = std::bit_cast<UnsignedT>(value);

    // truncate it
    if constexpr (BitSize < sizeof(T) * 8) {
        constexpr UnsignedT mask = (1ULL << BitSize) - 1;
        bits &= mask;
    }

    // Use IByteCopyable interface for efficient storage operations
    const uint8_t* byte_data = std::bit_cast<const uint8_t*>(&bits);
    // Round up to bytes
    size_t byte_count = std::min(sizeof(bits), (BitSize + 7) / 8);

    storage_.CopyFromBytes(byte_data,
        sizeof(bits),
        0,
        // srcStart
        BitOffset / 8,
        // dstStart (convert bit offset to byte offset)
        byte_count); // copyCount
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ArbitrarySignedInt(const std::string& str, int base) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ArbitrarySignedInt(const std::string& str, int base)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ArbitrarySignedInt(const std::string& str, int base) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T, typename>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator=(T value) {
    // Create temporary and move-assign
    *this = ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>(value);
    return *this;
}

#endif //ARBITRARYSIGNEDINT_CONSTRUCTOR_INL
