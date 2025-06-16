//
// Created by Lumi on 25. 6. 15.
//

#include <string>
#include "../include/ArbitraryFloat.h"

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(float value) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(double value) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(long double value) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(T value) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const std::string& str) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(
    const ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace>& value) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(
    const ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace>& value) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator
=(T value) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator float() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator double() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long double() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long long() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned long long() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator int() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned int() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator short() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned short() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator char() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned char() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator bool() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t NewExp, size_t NewMant, typename NewMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator ArbitraryFloat<NewExp, NewMant, NewMemoryPlace>() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator
+() const {
    return this;
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator
-() const {
    return this.SetSignBit(!this.GetSignBit());
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+(
    const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-(
    const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*(
    const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/(
    const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+=(
    const ArbitraryFloat& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-=(
    const ArbitraryFloat& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*=(
    const ArbitraryFloat& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/=(
    const ArbitraryFloat& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator==(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator!=(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<=(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>=(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsFinite() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsInf() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNaN() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNormal() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSubnormal() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsZero() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignBit() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsPositive() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNegative() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
int ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sign() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetSignBit() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SetSignBit(bool sign) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t ExpSize, size_t ExpOffset, typename ExpMemoryPlace>
ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
GetRawExponent() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t ExpSize, size_t ExpOffset, typename ExpMemoryPlace>
ArbitrarySignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
GetExponent() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t MantSize, size_t MantOffset, typename MantMemoryPlace>
ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
GetMantissa() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t MantSize, size_t MantOffset, typename MantMemoryPlace>
ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
GetSignificand() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToString() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::BitRepresentation() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToDecimalString() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToHexString() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString(int precision) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
ToInt() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
ToUInt() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ceil() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Floor() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Trunc() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Round() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
RoundEven() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Abs() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cbrt() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp2() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp10() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Expm1() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log1p() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sin() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cos() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tan() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asin() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acos() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atan() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sinh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cosh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tanh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asinh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acosh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atanh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextUp() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
NextDown() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextAfter(
    const ArbitraryFloat& direction) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
Scalbn(int exp) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
Ldexp(int exp) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
CheckedAdd(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
CheckedSub(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
CheckedMul(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
CheckedDiv(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fma(
    const ArbitraryFloat& y, const ArbitraryFloat& z) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fms(
    const ArbitraryFloat& y, const ArbitraryFloat& z) const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Infinity() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
NegativeInfinity() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NaN() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::QuietNaN() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignalingNaN() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Zero() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NegativeZero() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::One() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinValue() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MaxValue() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Epsilon() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinSubnormal() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Pi() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::E() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2E() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10E() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln2() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln10() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt2() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt1_2() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tau() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::InvPi() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Inv2Pi() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToBeBytes() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToLeBytes() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToNeBytes() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromBeBytes(
    const std::array<uint8_t, ((ExpBits + ArbitraryFloat::MantissaBits + 1 + 7) >> 3)>& bytes) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromLeBytes(
    const std::array<uint8_t, ((ExpBits + ArbitraryFloat::MantissaBits + 1 + 7) >> 3)>& bytes) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromNeBytes(
    const std::array<uint8_t, ((ExpBits + ArbitraryFloat::MantissaBits + 1 + 7) >> 3)>& bytes) {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Normalize() {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSpecialValue() const {
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromComponents(
    bool sign, uint64_t exponent, uint64_t mantissa) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Abs(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmod(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Remainder(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, int> Remquo(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fma(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y,
    const ArbitraryFloat<E, M, MP>& z) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmax(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmin(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fdim(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp2(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp10(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Expm1(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log10(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log2(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log1p(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Pow(const ArbitraryFloat<E, M, MP>& base, const ArbitraryFloat<E, M, MP>& exp) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sqrt(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cbrt(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Rsqrt(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Hypot(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Hypot(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y,
    const ArbitraryFloat<E, M, MP>& z) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sin(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cos(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tan(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Asin(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Acos(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atan(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atan2(const ArbitraryFloat<E, M, MP>& y, const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, ArbitraryFloat<E, M, MP> > Sincos(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sinh(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cosh(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tanh(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Asinh(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Acosh(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atanh(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Erf(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Erfc(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tgamma(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Lgamma(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Ceil(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Floor(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Trunc(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Round(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nearbyint(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Rint(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, int> Frexp(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Ldexp(const ArbitraryFloat<E, M, MP>& x, int exp) {
}
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, ArbitraryFloat<E, M, MP> > Modf(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Scalbn(const ArbitraryFloat<E, M, MP>& x, int exp) {
}
template<size_t E, size_t M, typename MP>
int Ilogb(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Logb(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nextafter(const ArbitraryFloat<E, M, MP>& from, const ArbitraryFloat<E, M, MP>& to) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nexttoward(const ArbitraryFloat<E, M, MP>& from, const ArbitraryFloat<E, M, MP>& to) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Copysign(const ArbitraryFloat<E, M, MP>& mag, const ArbitraryFloat<E, M, MP>& sign) {
}
template<size_t E, size_t M, typename MP>
bool IsFinite(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
bool IsInf(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
bool IsNaN(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
bool IsNormal(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
bool SignBit(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
bool IsSubnormal(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
bool IsZero(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
bool IsEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
bool IsLess(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
bool IsLessEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
bool IsGreater(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
bool IsGreaterEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
bool IsUnordered(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> J0(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> J1(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Jn(int n, const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Y0(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Y1(const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Yn(int n, const ArbitraryFloat<E, M, MP>& x) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Degrees(const ArbitraryFloat<E, M, MP>& radians) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Radians(const ArbitraryFloat<E, M, MP>& degrees) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Lerp(const ArbitraryFloat<E, M, MP>& a, const ArbitraryFloat<E, M, MP>& b,
    const ArbitraryFloat<E, M, MP>& t) {
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Clamp(const ArbitraryFloat<E, M, MP>& value, const ArbitraryFloat<E, M, MP>& min_val,
    const ArbitraryFloat<E, M, MP>& max_val) {
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Add(const ArbitraryFloat<E1, M1, MP>& a,
    const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Mul(const ArbitraryFloat<E1, M1, MP>& a,
    const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Sub(const ArbitraryFloat<E1, M1, MP>& a,
    const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Div(const ArbitraryFloat<E1, M1, MP>& a,
    const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
}
