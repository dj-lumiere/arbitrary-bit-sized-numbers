//
// Created by Lumi on 25. 6. 15.
//

#include "../include/ArbitrarySignedInt.h"
#include "../include/ArbitraryUnsignedInt.h"

// == CONSTRUCTORS ==
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T, typename>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::ArbitrarySignedInt(T value) {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::ArbitrarySignedInt(const std::string& str, int base) {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T, typename>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
=(T value) {
    throw std::runtime_error("Not implemented");
}

// == TYPE CONVERTERS ==
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator bool() const {
    return this->storage_;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator char() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator short() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator int() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator long() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator long long() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned char() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned short() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned int() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned long() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned long long() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<size_t NewBitSize, size_t NewBitOffset, typename NewMemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator ArbitrarySignedInt<NewBitSize, NewBitOffset,
    NewMemoryPlace>() const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<size_t UBitSize, size_t UBitOffset, typename UMemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UMemoryPlace>()
const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator+(
    const ArbitrarySignedInt& other) const {
    auto result = this->operator+(other);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator-(
    const ArbitrarySignedInt& other) const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator*(
    const ArbitrarySignedInt& other) const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator/(
    const ArbitrarySignedInt& other) const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator%(
    const ArbitrarySignedInt& other) const {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator-(
) const {
    return this->operator~()++;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator+(
) const {
    return this;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator+=(
    const ArbitrarySignedInt& other) {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator-=(
    const ArbitrarySignedInt& other) {
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator*=(
    const ArbitrarySignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator/=(
    const ArbitrarySignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator%=(
    const ArbitrarySignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator&(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator|(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator^(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
~() const {
    
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator<<(
    size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator>>
(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator&=(
    const ArbitrarySignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator|=(
    const ArbitrarySignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator^=(
    const ArbitrarySignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
<<=(size_t shift) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
>>=(size_t shift) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator==(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator!=(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator<(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator<=(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator>(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator>=(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator++() {
    
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
++(int) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator--() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
--(int) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::GetBit(size_t index) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::SetBit(size_t index) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::ClearBit(size_t index) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::FlipBit(size_t index) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::IsNegative() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::IsPositive() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Abs() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
int ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Sign() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::CountLeadingZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::CountTrailingZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::PopCount() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::ToString(int base) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::ToBinaryString() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::ToHexString() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::BitRepresentation() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Max() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Min() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> >
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::DivRem(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> >
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::DivEuclid(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::RemEuclid(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Pow(
    const ArbitrarySignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
Pow(size_t exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedAdd(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedSub(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedMul(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedDiv(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedRem(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedNeg() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedAbs() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedPow(const ArbitrarySignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::SaturatingAdd(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::SaturatingSub(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::SaturatingMul(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingAbs() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingNeg() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::SaturatingPow(
    const ArbitrarySignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::WrappingAdd(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::WrappingSub(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::WrappingMul(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::WrappingDiv(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::WrappingRem(
    const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingNeg() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingAbs() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::WrappingPow(
    const ArbitrarySignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingShl(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingShr(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingAdd(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingSub(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingMul(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingDiv(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingRem(const ArbitrarySignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingNeg() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingAbs() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingPow(const ArbitrarySignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingShl(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
::OverflowingShr(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::CountOnes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::CountZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::LeadingZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::TrailingZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::LeadingOnes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::TrailingOnes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
RotateLeft(size_t n) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
RotateRight(size_t n) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
ReverseBits() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
SwapBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::IsZero() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
Signum() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T>
std::optional<T> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::TryInto() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
NextPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedNextPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
PreviousPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> > ArbitrarySignedInt<
    BitSize, BitOffset, MemoryPlace>::
CheckedPreviousPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::IsPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
ToBeBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
ToLeBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
ToNeBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::FromBeBytes(
    const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::FromLeBytes(
    const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::FromNeBytes(
    const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Normalize() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::SignExtend() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> Abs(
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& value) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> Gcd(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> Lcm(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> CarryingAdd(
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b, bool carry) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool> BorrowingSub(
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b, bool borrow) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize * 2, BitOffset, MemoryPlace> WideningLcm(
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize * 2, BitOffset, MemoryPlace> WideningMul(
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b) {
}
