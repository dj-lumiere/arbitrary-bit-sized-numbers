//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_BIT_ANALYSIS_INL
#define ARBITRARYUNSIGNEDINT_BIT_ANALYSIS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountOnes() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountOnes() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountOnes() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountZeros() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountZeros() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountZeros() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingZeros() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingZeros() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingZeros() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingZeros() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingZeros() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingZeros() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingOnes() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingOnes() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingOnes() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingOnes() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingOnes() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingOnes() const not implemented.");
}

#endif //ARBITRARYUNSIGNEDINT_BIT_ANALYSIS_INL
