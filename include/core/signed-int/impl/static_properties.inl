//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_STATIC_PROPERTIES_INL
#define ARBITRARYSIGNEDINT_STATIC_PROPERTIES_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::IsNegative() const {
    return storage_.GetBit(BitSize - 1);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::IsPositive() const {
    return !storage_.GetBit(BitSize - 1) && !storage_.IsZero();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
int ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Sign() const {
    if (storage_.IsZero()) {
        return 0;
    }
    return storage_.GetBit(BitSize - 1) ?
               -1 :
               1;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Max() {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> max;
    max.storage_.SetAllBits();
    return max;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Min() {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> min;
    min.storage_.ClearAllBits();
    min.storage_.SetBit(BitSize + BitOffset - 1, true);
    return min;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::IsZero() const {
    return storage_.IsAllZeros();
}

#endif //ARBITRARYSIGNEDINT_STATIC_PROPERTIES_INL
