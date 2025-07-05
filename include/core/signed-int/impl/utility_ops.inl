//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_UTILITY_OPS_INL
#define ARBITRARYSIGNEDINT_UTILITY_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Abs() const {
    this->storage_.ClearBit(BitSize - 1);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> >
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::DivRem(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > DivRem(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::DivRem(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> >
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::DivEuclid(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > DivEuclid(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::DivEuclid(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::RemEuclid(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::RemEuclid(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::RemEuclid(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Pow(const ArbitrarySignedInt& exp) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Pow(const ArbitrarySignedInt& exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Pow(const ArbitrarySignedInt& exp) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Pow(size_t exp) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Pow(size_t exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Pow(size_t exp) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T>
std::optional<T> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::TryInto() const {
    // TODO: Implement std::optional<T> TryInto() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::TryInto() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNextPowerOfTwo() const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedNextPowerOfTwo() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNextPowerOfTwo() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPreviousPowerOfTwo() const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedPreviousPowerOfTwo() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPreviousPowerOfTwo() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::IsPowerOfTwo() const {
    // TODO: Implement bool IsPowerOfTwo() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::IsPowerOfTwo() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Normalize() {
    // TODO: Implement void Normalize() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Normalize() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SignExtend() {
    // TODO: Implement void SignExtend() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SignExtend() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> Abs(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& value) {
    // TODO: Implement Abs(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& value) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Abs(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& value) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> Gcd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    // TODO: Implement Gcd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Gcd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> Lcm(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    // TODO: Implement Lcm(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Lcm(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> CarryingAdd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry) {
    // TODO: Implement CarryingAdd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CarryingAdd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> BorrowingSub(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow) {
    // TODO: Implement BorrowingSub(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::BorrowingSub(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize * 2, BitOffset, StorageProviderType> WideningLcm(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    // TODO: Implement WideningLcm(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WideningLcm(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize * 2, BitOffset, StorageProviderType> WideningMul(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    // TODO: Implement WideningMul(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WideningMul(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
}

#endif //ARBITRARYSIGNEDINT_UTILITY_OPS_INL
