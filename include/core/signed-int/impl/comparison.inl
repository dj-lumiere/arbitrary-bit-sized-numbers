//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_COMPARISON_INL
#define ARBITRARYSIGNEDINT_COMPARISON_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator==(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator==(const ArbitrarySignedInt& other)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator==(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator!=(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator!=(const ArbitrarySignedInt& other)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator!=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<(const ArbitrarySignedInt& other)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=(const ArbitrarySignedInt& other)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>(const ArbitrarySignedInt& other)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>=(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>=(const ArbitrarySignedInt& other)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::partial_ordering ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=>(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::partial_ordering ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=>(const ArbitrarySignedInt& other)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=>(const ArbitrarySignedInt& other) not implemented.");
}

#endif //ARBITRARYSIGNEDINT_COMPARISON_INL
