//
// Created by Lumi on 25. 6. 15.
//

#ifndef ARBITRARYSIGNEDINT_H
#define ARBITRARYSIGNEDINT_H
#include <cstdint>
#include <optional>
#include <string>
#include <type_traits>
#include <array>
#include <iostream>
#include <utility>

#include "../include/interfaces/IStorage.h"
#include "ArbitraryUnsignedInt.h"

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
/**
 * @brief Represents an arbitrary-sized signed integer with customizable size, offset, and memory location.
 *
 * This class provides a comprehensive set of operations for arbitrary-sized signed integers,
 * including arithmetic, bitwise, comparison, utility, and conversion functions.
 * The size and memory layout of the integer are configurable via template parameters.
 *
 * @tparam BitSize The number of bits used to store the integer, must be greater than 1.
 * @tparam BitOffset The bit offset for memory alignment, must be in the range [0, 7].
 * @tparam MemoryPlace The underlying storage mechanism.
 */
class ArbitrarySignedInt {
    static_assert(BitSize > 1, "Signed int size must be greater than 1");
    static_assert(BitOffset < 8, "Bit offset must be in range [0,7]");

public:
    // Constructors
    ArbitrarySignedInt() = default;
    ArbitrarySignedInt(const ArbitrarySignedInt& other) = default;
    ArbitrarySignedInt(ArbitrarySignedInt&& other) = default;

    // Constructor from integral types
    template<typename T, typename = std::enable_if_t<std::is_integral_v<T> > >
    ArbitrarySignedInt(T value);

    // Constructor from string (binary, hex, or decimal)
    explicit ArbitrarySignedInt(const std::string& str, int base = 10);

    // Assignment operators
    ArbitrarySignedInt& operator=(const ArbitrarySignedInt& other) = default;
    ArbitrarySignedInt& operator=(ArbitrarySignedInt&& other) = default;

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T> > >
    ArbitrarySignedInt& operator=(T value);

    // Conversion operators
    explicit operator bool() const;
    explicit operator char() const;
    explicit operator short() const;
    explicit operator int() const;
    explicit operator long() const;
    explicit operator long long() const;
    explicit operator unsigned char() const;
    explicit operator unsigned short() const;
    explicit operator unsigned int() const;
    explicit operator unsigned long() const;
    explicit operator unsigned long long() const;

    // Different size/offset conversions
    template<size_t NewBitSize, size_t NewBitOffset, typename NewMemoryPlace>
    explicit operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewMemoryPlace>() const;

    // Conversion to/from unsigned
    template<size_t UBitSize, size_t UBitOffset, typename UMemoryPlace>
    explicit operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UMemoryPlace>() const;

    // Arithmetic operators
    ArbitrarySignedInt operator+(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt operator-(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt operator*(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt operator/(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt operator%(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt operator-() const; // unary minus
    ArbitrarySignedInt operator+() const; // unary plus

    // Assignment arithmetic operators
    ArbitrarySignedInt& operator+=(const ArbitrarySignedInt& other);
    ArbitrarySignedInt& operator-=(const ArbitrarySignedInt& other);
    ArbitrarySignedInt& operator*=(const ArbitrarySignedInt& other);
    ArbitrarySignedInt& operator/=(const ArbitrarySignedInt& other);
    ArbitrarySignedInt& operator%=(const ArbitrarySignedInt& other);

    // Bitwise operators (two's complement)
    ArbitrarySignedInt operator&(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt operator|(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt operator^(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt operator~() const;
    ArbitrarySignedInt operator<<(size_t shift) const;
    ArbitrarySignedInt operator>>(size_t shift) const; // arithmetic right shift

    // Assignment bitwise operators
    ArbitrarySignedInt& operator&=(const ArbitrarySignedInt& other);
    ArbitrarySignedInt& operator|=(const ArbitrarySignedInt& other);
    ArbitrarySignedInt& operator^=(const ArbitrarySignedInt& other);
    ArbitrarySignedInt& operator<<=(size_t shift);
    ArbitrarySignedInt& operator>>=(size_t shift);

    // Comparison operators
    bool operator==(const ArbitrarySignedInt& other) const;
    bool operator!=(const ArbitrarySignedInt& other) const;
    bool operator<(const ArbitrarySignedInt& other) const;
    bool operator<=(const ArbitrarySignedInt& other) const;
    bool operator>(const ArbitrarySignedInt& other) const;
    bool operator>=(const ArbitrarySignedInt& other) const;

    // Increment/decrement
    ArbitrarySignedInt& operator++(); // prefix
    ArbitrarySignedInt operator++(int); // postfix
    ArbitrarySignedInt& operator--(); // prefix
    ArbitrarySignedInt operator--(int); // postfix

    // Bit manipulation
    bool GetBit(size_t index) const;
    void SetBit(size_t index);
    void ClearBit(size_t index);
    void FlipBit(size_t index);

    // Sign operations
    bool IsNegative() const;
    bool IsPositive() const;
    ArbitrarySignedInt Abs() const;
    int Sign() const; // returns -1, 0, or 1

    // Utility functions
    size_t CountLeadingZeros() const;
    size_t CountTrailingZeros() const;
    size_t PopCount() const; // count of set bits

    // String representations
    std::string ToString(int base = 10) const;
    std::string ToBinaryString() const;
    std::string ToHexString() const;
    std::string BitRepresentation() const;

    // I/O operators
    friend std::ostream& operator<<(std::ostream& os, const ArbitrarySignedInt& value) {
        return os << value.ToString();
    }
    friend std::istream& operator>>(std::istream& is, ArbitrarySignedInt& value) {
        throw std::runtime_error("Not implemented");
    }

    // Size information
    static constexpr size_t GetBitSize() {
        return BitSize;
    }
    static constexpr size_t GetBitOffset() {
        return BitOffset;
    }

    // Special values
    static ArbitrarySignedInt Max();
    static ArbitrarySignedInt Min();

    // For internal use by ArbitraryFloat
    const auto& GetStorage() const {
        return storage_;
    }
    auto& GetStorage() {
        return storage_;
    }

    // Division operations with both quotient and remainder
    std::pair<ArbitrarySignedInt, ArbitrarySignedInt> DivRem(const ArbitrarySignedInt& other) const;
    std::pair<ArbitrarySignedInt, ArbitrarySignedInt> DivEuclid(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt RemEuclid(const ArbitrarySignedInt& other) const;

    // Power operations
    ArbitrarySignedInt Pow(const ArbitrarySignedInt& exp) const;
    ArbitrarySignedInt Pow(size_t exp) const;

    // Checked arithmetic operations (return std::optional or throw on overflow)
    std::optional<ArbitrarySignedInt> CheckedAdd(const ArbitrarySignedInt& other) const;
    std::optional<ArbitrarySignedInt> CheckedSub(const ArbitrarySignedInt& other) const;
    std::optional<ArbitrarySignedInt> CheckedMul(const ArbitrarySignedInt& other) const;
    std::optional<ArbitrarySignedInt> CheckedDiv(const ArbitrarySignedInt& other) const;
    std::optional<ArbitrarySignedInt> CheckedRem(const ArbitrarySignedInt& other) const;
    std::optional<ArbitrarySignedInt> CheckedNeg() const;
    std::optional<ArbitrarySignedInt> CheckedAbs() const;
    std::optional<ArbitrarySignedInt> CheckedPow(const ArbitrarySignedInt& exp) const;

    // Saturating arithmetic operations
    ArbitrarySignedInt SaturatingAdd(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt SaturatingSub(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt SaturatingMul(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt SaturatingAbs() const;
    ArbitrarySignedInt SaturatingNeg() const;
    ArbitrarySignedInt SaturatingPow(const ArbitrarySignedInt& exp) const;

    // Wrapping arithmetic operations
    ArbitrarySignedInt WrappingAdd(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt WrappingSub(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt WrappingMul(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt WrappingDiv(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt WrappingRem(const ArbitrarySignedInt& other) const;
    ArbitrarySignedInt WrappingNeg() const;
    ArbitrarySignedInt WrappingAbs() const;
    ArbitrarySignedInt WrappingPow(const ArbitrarySignedInt& exp) const;
    ArbitrarySignedInt WrappingShl(size_t shift) const;
    ArbitrarySignedInt WrappingShr(size_t shift) const;

    // Overflow-aware arithmetic that returns (result, overflow_flag)
    std::pair<ArbitrarySignedInt, bool> OverflowingAdd(const ArbitrarySignedInt& other) const;
    std::pair<ArbitrarySignedInt, bool> OverflowingSub(const ArbitrarySignedInt& other) const;
    std::pair<ArbitrarySignedInt, bool> OverflowingMul(const ArbitrarySignedInt& other) const;
    std::pair<ArbitrarySignedInt, bool> OverflowingDiv(const ArbitrarySignedInt& other) const;
    std::pair<ArbitrarySignedInt, bool> OverflowingRem(const ArbitrarySignedInt& other) const;
    std::pair<ArbitrarySignedInt, bool> OverflowingNeg() const;
    std::pair<ArbitrarySignedInt, bool> OverflowingAbs() const;
    std::pair<ArbitrarySignedInt, bool> OverflowingPow(const ArbitrarySignedInt& exp) const;
    std::pair<ArbitrarySignedInt, bool> OverflowingShl(size_t shift) const;
    std::pair<ArbitrarySignedInt, bool> OverflowingShr(size_t shift) const;

    // Bit operations
    size_t CountOnes() const;
    size_t CountZeros() const;
    size_t LeadingZeros() const;
    size_t TrailingZeros() const;
    size_t LeadingOnes() const;
    size_t TrailingOnes() const;
    ArbitrarySignedInt RotateLeft(size_t n) const;
    ArbitrarySignedInt RotateRight(size_t n) const;
    ArbitrarySignedInt ReverseBits() const;
    ArbitrarySignedInt SwapBytes() const;

    // Sign and comparison utilities
    bool IsZero() const;

    // Conversion utilities with bounds checking
    template<typename T>
    std::optional<T> TryInto() const;

    // Next/previous power of two
    ArbitrarySignedInt NextPowerOfTwo() const;
    std::optional<ArbitrarySignedInt> CheckedNextPowerOfTwo() const;
    ArbitrarySignedInt PreviousPowerOfTwo() const;
    std::optional<ArbitrarySignedInt> CheckedPreviousPowerOfTwo() const;
    bool IsPowerOfTwo() const;

    // Fixed to/from bytes conversion
    std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToBeBytes() const; // big endian
    std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToLeBytes() const; // little endian
    std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToNeBytes() const; // native endian
    static ArbitrarySignedInt FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes);
    static ArbitrarySignedInt FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes);
    static ArbitrarySignedInt FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes);

private:
    static constexpr size_t storage_bytes = (BitSize + BitOffset + 7) >> 3;
    using storage_type = typename MemoryPlace::template storage_type<storage_bytes>;

    storage_type storage_;

    // Helper functions
    void Normalize(); // Ensure proper sign extension
    void SignExtend(); // Extend sign bit to unused bits
};

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
Abs(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& value);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
Gcd(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>
Lcm(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool>
CarryingAdd(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b,
    bool carry);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>, bool>
BorrowingSub(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b,
    bool borrow);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize * 2, BitOffset, MemoryPlace>
WideningLcm(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize * 2, BitOffset, MemoryPlace>
WideningMul(const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& b);

// Utility type aliases for common formats
template<typename MemoryPlace>
using Int8 = ArbitrarySignedInt<8, 0, MemoryPlace>;

template<typename MemoryPlace>
using Int16 = ArbitrarySignedInt<16, 0, MemoryPlace>;

template<typename MemoryPlace>
using Int32 = ArbitrarySignedInt<32, 0, MemoryPlace>;

template<typename MemoryPlace>
using Int64 = ArbitrarySignedInt<64, 0, MemoryPlace>;

template<typename MemoryPlace>
using Int128 = ArbitrarySignedInt<128, 0, MemoryPlace>;

template<typename MemoryPlace>
using Int256 = ArbitrarySignedInt<256, 0, MemoryPlace>;

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

// == SIGNED INTEGER TYPE CONVERT == 
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator char() const {
    // ASI -> char?

    // 일단 이거 여기에 있으면 컴파일 무조건 안 되니까
    // 헤더를 만들어서 거기에 넣으세요라
    // ㅇㅇ 구현도 거기에 옮기세요라 안 그럼 ᄛᅵ크 터짐
    // 넣을 순 있죠 inline 먹여서 바로 그거다
    // 어차피 템플릿 들어간 시점에서 쌩인라인인데 님이 ㅁ

    // 애초에 뭐 완성된 거부터 없어서 지금 저 수많은 runtime_error를 보면
    // 그거 헤더 만들어진건데
    // ArbitrarySignedInt.h ㄱ
    // ?
    // 근데 거기에서 구현체 못 넣잖아
    // 그리고 

    // 일단 기본 헤더부터 터짐 (?)
    // 안 되면 그냥 0번 바이트 그대로 땡겨도 안 됨?
    // 근데 이거 ASI에서 char로 바꾸는거잖아

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

// == UNSIGNED INTEGER TYPE CONVERT ==
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned char() const {
    return storage_[0];
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

// == ARITHMETIC OPERATIONS ==

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

// == UNARY ARITHMETIC OPERATIONS ==

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
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator++() {
    storage_.Increment();
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
++(int) {
    ArbitrarySignedInt temp = *this;
    storage_.Increment();
    return temp;
}

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator--() {
    storage_.Decrement();
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
--(int) {
    ArbitrarySignedInt temp = *this;
    storage_.Decrement();
    return temp;
}

// == ARITHMETIC ASSIGN OPERATIONS == 
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

// == BITWISE OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator&(
    const ArbitrarySignedInt& other) const {
    ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> result;
    result.storage_ = this->storage_;
    result.storage_.BitwiseAnd(other->storage_);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator|(
    const ArbitrarySignedInt& other) const {
    ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> result;
    result.storage_ = this->storage_;
    result.storage_.BitwiseOr(other->storage_);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator^(
    const ArbitrarySignedInt& other) const {
    ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> result;
    result.storage_ = this->storage_;
    result.storage_.BitwiseXor(other->storage_);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
~() const {
    ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> result;
    result.storage_ = this->storage_;
    result.storage_.BitwiseNot();
    return result;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator<<(
    size_t shift) const {
    ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> result;
    result.storage_ = this->storage_;
    result.storage_.ShiftLeft(shift);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator>>
(size_t shift) const {
    ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> result;
    result.storage_ = this->storage_;
    result.storage_.ShiftRight(shift);
    return result;
}

// == BITWISE ASSIGN OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator&=(
    const ArbitrarySignedInt& other) {
    this->storage_.BitwiseAnd(other->storage_);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator|=(
    const ArbitrarySignedInt& other) {
    this->storage_.BitwiseOr(other->storage_);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator^=(
    const ArbitrarySignedInt& other) {
    this->storage_.BitwiseXor(other->storage_);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
<<=(size_t shift) {
    this->storage_.ShiftLeft(shift);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>& ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::operator
>>=(size_t shift) {
    this->storage_.ShiftRight(shift);
    return *this;
}

// == COMPARISON OPERATIONS ==

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
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::GetBit(size_t index) const {
    storage_.GetBit(index);
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::SetBit(size_t index) {
    storage_.SetBit(index);
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::ClearBit(size_t index) {
    storage_.ClearBit(index);
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::FlipBit(size_t index) {
    storage_.FlipBit(index);
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::IsNegative() const {
    return storage_.GetBit(BitSize - 1);
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::IsPositive() const {
    return !storage_.GetBit(BitSize - 1) && !storage_.IsZero();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Abs() const {
    storage_.ClearBit(BitSize - 1);
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
int ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Sign() const {
    if (storage_.IsZero()) {
        return 0;
    }
    return storage_.GetBit(BitSize - 1) ? -1 : 1;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::CountLeadingZeros() const {
    return storage_.CountLeadingZeros();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::CountTrailingZeros() const {
    return storage_.CountTrailingZeros();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::PopCount() const {
    return storage_.PopCount();
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
    ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> max;
    max.storage_.SetAllBits();
    return max;
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::Min() {
    ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> max;
    max.storage_.ClearAllBits();
    return max;
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
    return storage_.CountOnes();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::CountZeros() const {
    return storage_.CountZeros();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::LeadingZeros() const {
    return storage_.LeadingZeros();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::TrailingZeros() const {
    return storage_.TrailingZeros();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::LeadingOnes() const {
    return storage_.LeadingOnes();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::TrailingOnes() const {
    return storage_.TrailingOnes();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
RotateLeft(size_t n) const {
    return storage_.RotateLeft(n);
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
RotateRight(size_t n) const {
    return storage_.RotateRight(n);
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
ReverseBits() const {
    return storage_.ReverseBits();
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace> ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::
SwapBytes() const {
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitrarySignedInt<BitSize, BitOffset, MemoryPlace>::IsZero() const {
    return storage_.IsAllZeros();
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

#endif //ARBITRARYSIGNEDINT_H
