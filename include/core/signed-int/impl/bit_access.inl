//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_BIT_ACCESS_INL
#define ARBITRARYSIGNEDINT_BIT_ACCESS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::GetBit(size_t index) const {
    return storage_.GetBit(index);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SetBit(size_t index) {
    storage_.SetBit(index);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ClearBit(size_t index) {
    storage_.ClearBit(index);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FlipBit(size_t index) {
    storage_.FlipBit(index);
}

#endif //ARBITRARYSIGNEDINT_BIT_ACCESS_INL
