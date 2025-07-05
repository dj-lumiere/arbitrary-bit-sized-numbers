//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_STATIC_PROPERTIES_INL
#define ARBITRARYUNSIGNEDINT_STATIC_PROPERTIES_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Max() {
    auto result = ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>();
    result.storage_.SetAllBits();
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Min() {
    auto result = ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>();
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::IsZero() const {
    for (size_t i = 0; i < BitSize; ++i) {
        if (this->GetBit(i)) {
            return false;
        }
    }
    return true;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Signum() const {
    return IsZero() ?
               0 :
               1;
}

#endif //ARBITRARYUNSIGNEDINT_STATIC_PROPERTIES_INL
