//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_CONVERSIONS_INL
#define ARBITRARYUNSIGNEDINT_CONVERSIONS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator bool() const {
    return not this->storage_.IsZero();
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned char() const {
    unsigned char result = 0;
    size_t byteOffset = BitOffset / 8;
    size_t bitOffset = BitOffset % 8;
    result |= storage_[byteOffset] >> bitOffset;
    if (storage_.GetByteSize() > 1 + byteOffset && BitSize >= 8 - bitOffset) {
        result |= storage_[1 + byteOffset] << (8 - bitOffset);
    }
    if (BitSize < 8) {
        result &= (1 << BitSize) - 1;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned short() const {
    unsigned short result = 0;
    size_t targetByteSize = sizeof(result);
    for (int i = 0; i < std::min(targetByteSize, storage_.GetByteSize()); i++) {
        result |= storage_[i];
        result <<= 8;
    }
    result >>= BitOffset;
    if (storage_.GetByteSize() > targetByteSize && BitSize >= 8 - BitOffset) {
        result |= storage_[targetByteSize] << (8 - BitOffset);
    }
    if (BitSize < 8 * targetByteSize) {
        result &= (1ULL << BitSize) - 1;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned int() const {
    unsigned int result = 0;
    size_t targetByteSize = sizeof(result);
    result = storage_[0] >> BitOffset;
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long() const {
    unsigned long result = 0;
    size_t targetByteSize = sizeof(result);
    result = storage_[0] >> BitOffset;
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long long() const {
    unsigned long long result = 0;
    size_t targetByteSize = sizeof(result);
    result = storage_[0] >> BitOffset;
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<size_t NewBitSize, size_t NewBitOffset, typename NewStorageProvider>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitraryUnsignedInt<NewBitSize, NewBitOffset, NewStorageProvider>() const {
    auto result = ArbitraryUnsignedInt<NewBitSize, NewBitOffset, NewStorageProvider>();
    result.GetStorage().CopyBitsFrom(this->GetStorage(), BitOffset, std::min(BitSize, NewBitSize), NewBitOffset);
    return result;
}

#endif //ARBITRARYUNSIGNEDINT_CONVERSIONS_INL
