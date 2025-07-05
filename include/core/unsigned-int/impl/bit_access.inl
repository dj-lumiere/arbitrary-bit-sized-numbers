//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_BIT_ACCESS_INL
#define ARBITRARYUNSIGNEDINT_BIT_ACCESS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::GetBit(size_t index) const {
    return storage_.GetBit(index + BitOffset);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SetBit(size_t index, bool value) {
    storage_.SetBit(index + BitOffset, value);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ClearBit(size_t index) {
    storage_.ClearBit(index + BitOffset);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FlipBit(size_t index) {
    storage_.FlipBit(index + BitOffset);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountLeadingZeros() const {
    storage_.CountLeadingZeros();
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountTrailingZeros() const {
    storage_.CountTrailingZeros();
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::PopCount() const {
    storage_.PopCount();
}

#endif //ARBITRARYUNSIGNEDINT_BIT_ACCESS_INL
