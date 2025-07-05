//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_ARITHMETIC_INL
#define ARBITRARYSIGNEDINT_ARITHMETIC_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%(const ArbitrarySignedInt& other) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%=(const ArbitrarySignedInt& other) not implemented.");
}

#endif //ARBITRARYSIGNEDINT_ARITHMETIC_INL
