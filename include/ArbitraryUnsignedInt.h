//
// Created by Lumi on 25. 6. 15.
//

#ifndef ARBITRARYUNSIGNEDINT_H
#define ARBITRARYUNSIGNEDINT_H
#include <cstdint>
#include <optional>
#include <string>
#include <type_traits>
#include <array>
#include <iostream>
#include <utility>
#include "../include/interfaces/IStorage.h"

template<typename T, typename = void>
struct is_valid_storage : std::false_type {
};

template<typename T>
struct is_valid_storage<T, std::enable_if_t<
                            std::is_base_of_v<IStorage, T>
                        > > : std::true_type {
};

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
class ArbitraryUnsignedInt {
    static_assert(BitSize > 0, "Unsigned int size must be greater than 0");
    static_assert(BitOffset < 8, "Bit offset must be in range [0,7]");

public:
    // Constructors
    ArbitraryUnsignedInt() = default;
    ArbitraryUnsignedInt(const ArbitraryUnsignedInt& other) = default;
    ArbitraryUnsignedInt(ArbitraryUnsignedInt&& other) = default;

    // Constructor from integral types
    template<typename T, typename = std::enable_if_t<std::is_integral_v<T> > >
    explicit ArbitraryUnsignedInt(T value);

    // Constructor from string (binary, hex, or decimal)
    explicit ArbitraryUnsignedInt(const std::string& str, int base = 10);

    // Assignment operators
    ArbitraryUnsignedInt& operator=(const ArbitraryUnsignedInt& other) = default;
    ArbitraryUnsignedInt& operator=(ArbitraryUnsignedInt&& other) = default;

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T> > >
    ArbitraryUnsignedInt& operator=(T value);

    // Conversion operators
    explicit operator bool() const;
    explicit operator unsigned char() const;
    explicit operator unsigned short() const;
    explicit operator unsigned int() const;
    explicit operator unsigned long() const;
    explicit operator unsigned long long() const;

    // Different size/offset conversions
    template<size_t NewBitSize, size_t NewBitOffset, typename NewMemoryPlace>
    explicit operator ArbitraryUnsignedInt<NewBitSize, NewBitOffset, NewMemoryPlace>() const;

    // Arithmetic operators
    ArbitraryUnsignedInt operator+(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt operator-(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt operator*(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt operator/(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt operator%(const ArbitraryUnsignedInt& other) const;

    // Assignment arithmetic operators
    ArbitraryUnsignedInt& operator+=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator-=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator*=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator/=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator%=(const ArbitraryUnsignedInt& other);

    // Bitwise operators
    ArbitraryUnsignedInt operator&(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt operator|(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt operator^(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt operator~() const;
    ArbitraryUnsignedInt operator<<(size_t shift) const;
    ArbitraryUnsignedInt operator>>(size_t shift) const;

    // Assignment bitwise operators
    ArbitraryUnsignedInt& operator&=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator|=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator^=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator<<=(size_t shift);
    ArbitraryUnsignedInt& operator>>=(size_t shift);

    // Comparison operators
    bool operator==(const ArbitraryUnsignedInt& other) const;
    bool operator!=(const ArbitraryUnsignedInt& other) const;
    bool operator<(const ArbitraryUnsignedInt& other) const;
    bool operator<=(const ArbitraryUnsignedInt& other) const;
    bool operator>(const ArbitraryUnsignedInt& other) const;
    bool operator>=(const ArbitraryUnsignedInt& other) const;

    // Increment/decrement
    ArbitraryUnsignedInt& operator++(); // prefix
    ArbitraryUnsignedInt operator++(int); // postfix
    ArbitraryUnsignedInt& operator--(); // prefix
    ArbitraryUnsignedInt operator--(int); // postfix

    // Bit manipulation
    bool GetBit(size_t index) const;
    void SetBit(size_t index, bool value = true);
    void ClearBit(size_t index);
    void FlipBit(size_t index);

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
    friend std::ostream& operator<<(std::ostream& os, const ArbitraryUnsignedInt& value) {
        return os << value.ToString();
    }
    friend std::istream& operator>>(std::istream& is, ArbitraryUnsignedInt& value) {
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
    static ArbitraryUnsignedInt Max();
    static ArbitraryUnsignedInt Min(); // always 0 for unsigned

    // For internal use by ArbitraryFloat
    const auto& GetStorage() const {
        return storage_;
    }
    auto& GetStorage() {
        return storage_;
    }

    // Division operations with both quotient and remainder
    std::pair<ArbitraryUnsignedInt, ArbitraryUnsignedInt> DivRem(const ArbitraryUnsignedInt& other) const;

    // Power operations
    ArbitraryUnsignedInt Pow(const ArbitraryUnsignedInt& exp) const;
    ArbitraryUnsignedInt Pow(size_t exp) const;

    // Checked arithmetic operations (return std::optional or throw on overflow)
    std::optional<ArbitraryUnsignedInt> CheckedAdd(const ArbitraryUnsignedInt& other) const;
    std::optional<ArbitraryUnsignedInt> CheckedSub(const ArbitraryUnsignedInt& other) const;
    std::optional<ArbitraryUnsignedInt> CheckedMul(const ArbitraryUnsignedInt& other) const;
    std::optional<ArbitraryUnsignedInt> CheckedDiv(const ArbitraryUnsignedInt& other) const;
    std::optional<ArbitraryUnsignedInt> CheckedRem(const ArbitraryUnsignedInt& other) const;
    std::optional<ArbitraryUnsignedInt> CheckedPow(const ArbitraryUnsignedInt& exp) const;

    // Saturating arithmetic operations
    ArbitraryUnsignedInt SaturatingAdd(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt SaturatingSub(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt SaturatingMul(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt SaturatingPow(const ArbitraryUnsignedInt& exp) const;

    // Wrapping arithmetic operations
    ArbitraryUnsignedInt WrappingAdd(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt WrappingSub(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt WrappingMul(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt WrappingDiv(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt WrappingRem(const ArbitraryUnsignedInt& other) const;
    ArbitraryUnsignedInt WrappingPow(const ArbitraryUnsignedInt& exp) const;
    ArbitraryUnsignedInt WrappingShl(size_t shift) const;
    ArbitraryUnsignedInt WrappingShr(size_t shift) const;

    // Overflow-aware arithmetic that returns (result, overflow_flag)
    std::pair<ArbitraryUnsignedInt, bool> OverflowingAdd(const ArbitraryUnsignedInt& other) const;
    std::pair<ArbitraryUnsignedInt, bool> OverflowingSub(const ArbitraryUnsignedInt& other) const;
    std::pair<ArbitraryUnsignedInt, bool> OverflowingMul(const ArbitraryUnsignedInt& other) const;
    std::pair<ArbitraryUnsignedInt, bool> OverflowingDiv(const ArbitraryUnsignedInt& other) const;
    std::pair<ArbitraryUnsignedInt, bool> OverflowingRem(const ArbitraryUnsignedInt& other) const;
    std::pair<ArbitraryUnsignedInt, bool> OverflowingPow(const ArbitraryUnsignedInt& exp) const;
    std::pair<ArbitraryUnsignedInt, bool> OverflowingShl(size_t shift) const;
    std::pair<ArbitraryUnsignedInt, bool> OverflowingShr(size_t shift) const;

    // Bit operations
    size_t CountOnes() const;
    size_t CountZeros() const;
    size_t LeadingZeros() const;
    size_t TrailingZeros() const;
    size_t LeadingOnes() const;
    size_t TrailingOnes() const;
    ArbitraryUnsignedInt RotateLeft(size_t n) const;
    ArbitraryUnsignedInt RotateRight(size_t n) const;
    ArbitraryUnsignedInt ReverseBits() const;
    ArbitraryUnsignedInt SwapBytes() const;

    // Sign and comparison utilities
    bool IsZero() const;
    ArbitraryUnsignedInt Signum() const; // returns 0 or 1 (never negative for unsigned)

    // Conversion utilities with bounds checking
    template<typename T>
    std::optional<T> TryInto() const;

    // Next/previous power of two
    ArbitraryUnsignedInt NextPowerOfTwo() const;
    std::optional<ArbitraryUnsignedInt> CheckedNextPowerOfTwo() const;
    ArbitraryUnsignedInt PreviousPowerOfTwo() const;
    std::optional<ArbitraryUnsignedInt> CheckedPreviousPowerOfTwo() const;
    bool IsPowerOfTwo() const;

    // Fixed to/from bytes conversion
    std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToBeBytes() const; // big endian
    std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToLeBytes() const; // little endian
    std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToNeBytes() const; // native endian
    static ArbitraryUnsignedInt FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes);
    static ArbitraryUnsignedInt FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes);
    static ArbitraryUnsignedInt FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes);

private:
    static constexpr size_t storage_bytes = (BitSize + BitOffset + 7) >> 3;
    using storage_type = typename MemoryPlace::template storage_type<storage_bytes>;

    static_assert(std::derived_from<storage_type, IStorage>,
        "MemoryPlace::storage_type must implement IStorage");

    storage_type storage_;

    // Helper functions for arithmetic
    void Normalize(); // Ensure unused bits are zero
};

// Additional utility functions
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>
Gcd(const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>
Lcm(const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b);

// Wide multiplication (returns result in double-wide type)
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, MemoryPlace>
WideningMul(const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, MemoryPlace>
WideningLcm(const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool>
CarryingAdd(const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b,
    bool carry);

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool>
BorrowingSub(const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b,
    bool borrow);

// Utility type aliases for common formats
template<typename MemoryPlace>
using UInt8 = ArbitraryUnsignedInt<8, 0, MemoryPlace>;

template<typename MemoryPlace>
using UInt16 = ArbitraryUnsignedInt<16, 0, MemoryPlace>;

template<typename MemoryPlace>
using UInt32 = ArbitraryUnsignedInt<32, 0, MemoryPlace>;

template<typename MemoryPlace>
using UInt64 = ArbitraryUnsignedInt<64, 0, MemoryPlace>;

template<typename MemoryPlace>
using UInt128 = ArbitraryUnsignedInt<128, 0, MemoryPlace>;

template<typename MemoryPlace>
using UInt256 = ArbitraryUnsignedInt<256, 0, MemoryPlace>;

template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T, typename>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ArbitraryUnsignedInt(T value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ArbitraryUnsignedInt(const std::string& str, int base) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T, typename>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
=(T value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator bool() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned char() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned short() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned int() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned long() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator unsigned long long() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<size_t NewBitSize, size_t NewBitOffset, typename NewMemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator ArbitraryUnsignedInt<NewBitSize, NewBitOffset,
    NewMemoryPlace>() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator+(
    const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator-(
    const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator*(
    const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator/(
    const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator%(
    const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
+=(const ArbitraryUnsignedInt& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
-=(const ArbitraryUnsignedInt& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
*=(const ArbitraryUnsignedInt& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
/=(const ArbitraryUnsignedInt& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
%=(const ArbitraryUnsignedInt& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator&(
    const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator|(
    const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator^(
    const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
~() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
<<(size_t shift) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
>>(size_t shift) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
&=(const ArbitraryUnsignedInt& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
|=(const ArbitraryUnsignedInt& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
^=(const ArbitraryUnsignedInt& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
<<=(size_t shift) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
>>=(size_t shift) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator==(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator!=(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator<(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator<=(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator>(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator>=(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
++() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
++(int) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
--() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::operator
--(int) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::GetBit(size_t index) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::SetBit(size_t index, bool value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ClearBit(size_t index) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::FlipBit(size_t index) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::CountLeadingZeros() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::CountTrailingZeros() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::PopCount() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ToString(int base) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ToBinaryString() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::ToHexString() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::BitRepresentation() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::Max() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::Min() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> >
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::DivRem(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::Pow(
    const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
Pow(size_t exp) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedAdd(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedSub(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedMul(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedDiv(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedRem(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedPow(const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingAdd(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingSub(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingMul(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SaturatingPow(const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingAdd(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingSub(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingMul(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingDiv(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingRem(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingPow(const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingShl(size_t shift) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
WrappingShr(size_t shift) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingAdd(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingSub(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingMul(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingDiv(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingRem(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingPow(const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingShl(size_t shift) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::OverflowingShr(size_t shift) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::CountOnes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::CountZeros() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::LeadingZeros() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::TrailingZeros() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::LeadingOnes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::TrailingOnes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
RotateLeft(size_t n) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
RotateRight(size_t n) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
ReverseBits() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
SwapBytes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::IsZero() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
Signum() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
template<typename T>
std::optional<T> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::TryInto() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
NextPowerOfTwo() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedNextPowerOfTwo() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
PreviousPowerOfTwo() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> > ArbitraryUnsignedInt<BitSize, BitOffset,
    MemoryPlace>::CheckedPreviousPowerOfTwo() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
bool ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::IsPowerOfTwo() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
ToBeBytes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
ToLeBytes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
ToNeBytes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::
FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
void ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>::Normalize() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> Gcd(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace> Lcm(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, MemoryPlace> WideningMul(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, MemoryPlace> WideningLcm(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> CarryingAdd(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b, bool carry) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t BitSize, size_t BitOffset, typename MemoryPlace>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>, bool> BorrowingSub(
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& a,
    const ArbitraryUnsignedInt<BitSize, BitOffset, MemoryPlace>& b, bool borrow) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}

#endif //ARBITRARYUNSIGNEDINT_H
