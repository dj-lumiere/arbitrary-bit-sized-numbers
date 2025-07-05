//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_UNARY_OPS_INL
#define ARBITRARYUNSIGNEDINT_UNARY_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator++() {
    storage_.Increment();
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator++(int) {
    ArbitraryUnsignedInt temp = *this;
    storage_.Increment();
    return temp;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator--() {
    storage_.Decrement();
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator--(int) {
    ArbitraryUnsignedInt temp = *this;
    storage_.Decrement();
    return temp;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator~() const {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = storage_.ByteNot();
    return result;
}

#endif //ARBITRARYUNSIGNEDINT_UNARY_OPS_INL
