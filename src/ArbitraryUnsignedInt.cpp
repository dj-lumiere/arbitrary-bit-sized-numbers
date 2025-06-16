//
// Created by Lumi on 25. 6. 15.
//

#include "../include/ArbitraryUnsignedInt.h"

#include <cstdint>
#include <optional>
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T, typename>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ArbitraryUnsignedInt(T value) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ArbitraryUnsignedInt(const std::string& str, int base) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T, typename>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
=(T value) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator bool() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned char() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned short() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned int() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned long() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned long long() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<size_t NewBitSize, size_t NewBitOffset, typename NewMemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator ArbitraryUnsignedInt<NewBitSize, NewBitOffset,
    NewMemoryPlace>() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator+(
    const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator-(
    const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator*(
    const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator/(
    const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator%(
    const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
+=(const ArbitraryUnsignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
-=(const ArbitraryUnsignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
*=(const ArbitraryUnsignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
/=(const ArbitraryUnsignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
%=(const ArbitraryUnsignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator&(
    const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator|(
    const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator^(
    const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
~() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
<<(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
>>(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
&=(const ArbitraryUnsignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
|=(const ArbitraryUnsignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
^=(const ArbitraryUnsignedInt& other) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
<<=(size_t shift) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
>>=(size_t shift) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator==(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator!=(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator<(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator<=(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator>(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator>=(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
++() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
++(int) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
--() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
--(int) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::GetBit(size_t index) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::SetBit(size_t index, bool value) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ClearBit(size_t index) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::FlipBit(size_t index) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::CountLeadingZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::CountTrailingZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::PopCount() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ToString(int base) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ToBinaryString() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ToHexString() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::BitRepresentation() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::Max() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::Min() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> >
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::DivRem(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::Pow(
    const ArbitraryUnsignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
Pow(size_t exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedAdd(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedSub(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedMul(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedDiv(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedRem(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedPow(const ArbitraryUnsignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingAdd(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingSub(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingMul(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingPow(const ArbitraryUnsignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingAdd(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingSub(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingMul(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingDiv(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingRem(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingPow(const ArbitraryUnsignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingShl(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingShr(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingAdd(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingSub(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingMul(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingDiv(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingRem(const ArbitraryUnsignedInt& other) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingPow(const ArbitraryUnsignedInt& exp) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingShl(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingShr(size_t shift) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::CountOnes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::CountZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::LeadingZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::TrailingZeros() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::LeadingOnes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::TrailingOnes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
RotateLeft(size_t n) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
RotateRight(size_t n) const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
ReverseBits() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SwapBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::IsZero() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
Signum() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T>
std::optional<T> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::TryInto() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
NextPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedNextPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
PreviousPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedPreviousPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::IsPowerOfTwo() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
ToBeBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
ToLeBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
ToNeBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::Normalize() {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> Gcd(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> Lcm(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, MemoryPlace> WideningMul(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, MemoryPlace> WideningLcm(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> CarryingAdd(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b, bool carry) {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> BorrowingSub(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b, bool borrow) {
}
