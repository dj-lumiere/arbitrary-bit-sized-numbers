//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_CONVERSIONS_INL
#define ARBITRARYSIGNEDINT_CONVERSIONS_INL

// == TYPE CONVERTERS ==
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator bool() const {
    return this->storage_;
}

// == SIGNED INTEGER TYPE CONVERT == 
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator char() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator char() const
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator char() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator short() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator short() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator short() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator int() const {
    int result = 0;
    for (size_t i = 0; i < BitSize && i < sizeof(int) * 8; ++i) {
        if (storage_.GetBit(i)) {
            result |= (1 << i);
        }
    }
    if (IsNegative()) {
        return -result;
    }
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long long() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long long() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long long() not implemented.");
}

// == UNSIGNED INTEGER TYPE CONVERT ==
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned char() const {
    return storage_[0];
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned short() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned short() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned short() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned int() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned int() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned int() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long long() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long long() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long long() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<size_t NewBitSize, size_t NewBitOffset, typename NewStorageProviderType> requires StorageProvider<NewStorageProviderType, ((NewBitSize + NewBitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewStorageProviderType>() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewStorageProviderType>() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewStorageProviderType>() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<size_t UBitSize, size_t UBitOffset, typename UStorageProviderType> requires StorageProvider<UStorageProviderType, ((UBitSize + UBitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UStorageProviderType>() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UStorageProviderType>() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UStorageProviderType>() not implemented.");
}

#endif //ARBITRARYSIGNEDINT_CONVERSIONS_INL
