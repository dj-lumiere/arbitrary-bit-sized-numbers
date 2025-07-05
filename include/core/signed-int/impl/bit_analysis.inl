//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_BIT_ANALYSIS_INL
#define ARBITRARYSIGNEDINT_BIT_ANALYSIS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CountLeadingZeros() const {
    return storage_.CountLeadingZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CountTrailingZeros() const {
    return storage_.CountTrailingZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::PopCount() const {
    return storage_.PopCount();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CountOnes() const {
    return storage_.CountOnes();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CountZeros() const {
    return storage_.CountZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::LeadingZeros() const {
    return storage_.LeadingZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::TrailingZeros() const {
    return storage_.TrailingZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::LeadingOnes() const {
    return storage_.LeadingOnes();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::TrailingOnes() const {
    return storage_.TrailingOnes();
}

#endif //ARBITRARYSIGNEDINT_BIT_ANALYSIS_INL
