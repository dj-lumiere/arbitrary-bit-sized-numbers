//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_BITWISE_INL
#define ARBITRARYUNSIGNEDINT_BITWISE_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator&(const ArbitraryUnsignedInt& other) {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = storage_;
    result.storage_.ByteAnd(other.storage_);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator|(const ArbitraryUnsignedInt& other) {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = storage_;
    result.storage_.ByteOr(other.storage_);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator^(const ArbitraryUnsignedInt& other) {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = storage_;
    result.storage_.ByteXor(other.storage_);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator<<(size_t shift) const {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.ShiftLeft(shift);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator>>(size_t shift) const {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.ShiftRight(shift);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator&=(const ArbitraryUnsignedInt& other) {
    this->storage_.BitwiseAnd(other->storage_);
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator|=(const ArbitraryUnsignedInt& other) {
    this->storage_.BitwiseOr(other->storage_);
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator^=(const ArbitraryUnsignedInt& other) {
    this->storage_.BitwiseXor(other->storage_);
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator<<=(size_t shift) {
    this->storage_.ShiftLeft(shift);
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator>>=(size_t shift) {
    this->storage_.ShiftRight(shift);
    return *this;
}

#endif //ARBITRARYUNSIGNEDINT_BITWISE_INL
