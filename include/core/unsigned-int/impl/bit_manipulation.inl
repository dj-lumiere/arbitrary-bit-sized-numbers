//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_BIT_MANIPULATION_INL
#define ARBITRARYUNSIGNEDINT_BIT_MANIPULATION_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateLeft(size_t n) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateLeft(size_t n) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateLeft(size_t n) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateRight(size_t n) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateRight(size_t n) not implemented.
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateRight(size_t n) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBits() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBits() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBits() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() not implemented.");
}

#endif //ARBITRARYUNSIGNEDINT_BIT_MANIPULATION_INL
