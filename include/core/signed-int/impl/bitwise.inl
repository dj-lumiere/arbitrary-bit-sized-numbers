//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_BITWISE_INL
#define ARBITRARYSIGNEDINT_BITWISE_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator&(const ArbitrarySignedInt& other) const {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.BitwiseAnd(other->storage_);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator|(const ArbitrarySignedInt& other) const {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.BitwiseOr(other->storage_);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator^(const ArbitrarySignedInt& other) const {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.BitwiseXor(other->storage_);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<<(size_t shift) const {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.ShiftLeft(shift);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>>(size_t shift) const {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.ShiftRight(shift);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator&=(const ArbitrarySignedInt& other) {
    this->storage_.BitwiseAnd(other->storage_);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator|=(const ArbitrarySignedInt& other) {
    this->storage_.BitwiseOr(other->storage_);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator^=(const ArbitrarySignedInt& other) {
    this->storage_.BitwiseXor(other->storage_);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<<=(size_t shift) {
    this->storage_.ShiftLeft(shift);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>>=(size_t shift) {
    this->storage_.ShiftRight(shift);
    return *this;
}

#endif //ARBITRARYSIGNEDINT_BITWISE_INL
