//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_CONSTRUCTOR_INL
#define ARBITRARYUNSIGNEDINT_CONSTRUCTOR_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T, typename>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ArbitraryUnsignedInt(T value) : storage_() {
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

    if constexpr (std::endian::native == std::endian::big) {
        // Reverse bytes if native endian is big
        storage_.ReverseBytes();
    }
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ArbitraryUnsignedInt(const std::string& str, int base) {
    if (base < 2 || base > 36) {
        throw std::invalid_argument("Invalid base");
    }
    // Clear the storage first
    storage_.Clear();

    // Convert base to ArbitraryUnsignedInt
    ArbitraryUnsignedInt base_value(base);

    for (char c : str) {
        if ('0' <= c && c <= '9') {
            c -= '0';
        }
        else if ('a' <= c && c <= 'z') {
            c -= 'a' - 10;
        }
        else if ('A' <= c && c <= 'Z') {
            c -= 'A' - 10;
        }
        else {
            throw std::invalid_argument("Invalid character in string");
        }
        if (c >= base) {
            throw std::invalid_argument("Invalid character in string");
        }
        this->operator*=(base_value); // Now using ArbitraryUnsignedInt
        this->operator+=(ArbitraryUnsignedInt(c)); // Convert digit to ArbitraryUnsignedInt
    }
    this->Normalize();
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T, typename>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator=(T value) {
    // Create temporary and move-assign
    *this = ArbitraryUnsignedInt(value);
    return *this;
}

#endif //ARBITRARYUNSIGNEDINT_CONSTRUCTOR_INL
