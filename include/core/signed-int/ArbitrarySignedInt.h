//
// Created by Lumi on 25. 6. 15.
//

#ifndef ARBITRARYSIGNEDINT_H
#define ARBITRARYSIGNEDINT_H
#include <algorithm>
#include <optional>
#include <string>
#include <type_traits>
#include <array>
#include <iostream>
#include <utility>

#include "../../concepts/StorageProvider.h"

// Forward declaration - don't include the header
template<size_t BitSize, size_t BitOffset, typename StorageProviderType>
class ArbitraryUnsignedInt;

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
/**
 * @brief Represents an arbitrary-sized signed integer with customizable size, offset, and memory location.
 *
 * This class provides a comprehensive set of operations for arbitrary-sized signed integers,
 * including arithmetic, bitwise, comparison, utility, and conversion functions.
 * The size and memory layout of the integer are configurable via template parameters.
 *
 * @tparam BitSize The number of bits used to store the integer. It must be greater than 1.
 * @tparam BitOffset The bit offset for memory alignment.
 * @tparam StorageProvider The underlying storage provider.
 */
class ArbitrarySignedInt {
    static_assert(BitSize > 1, "Signed int size must be greater than 1");
    static constexpr size_t storageBytes = (BitSize + BitOffset + 7) >> 3;
    using StorageType = typename StorageProviderType::template StorageType<storageBytes>;
    StorageType storage_;

public:
    // Constructors
    ArbitrarySignedInt() = default;
    ArbitrarySignedInt(const ArbitrarySignedInt& other) = default;
    ArbitrarySignedInt(ArbitrarySignedInt&& other) = default;

    // Constructor from integral types
    template<typename T, typename = std::enable_if_t<std::is_integral_v<T> > >
    ArbitrarySignedInt(T value);

    // Constructor from string (binary, hex, or decimal)
    ArbitrarySignedInt(const char* str, int base = 10)
        : ArbitrarySignedInt(std::string(str), base) // ← Correct delegating constructor
    {
        // Body can be empty
    }
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
    template<size_t NewBitSize, size_t NewBitOffset, typename NewStorageProviderType> requires StorageProvider<NewStorageProviderType, ((NewBitSize + NewBitOffset + 7) >> 3)>
    explicit operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewStorageProviderType>() const;

    // Conversion to/from unsigned
    template<size_t UBitSize, size_t UBitOffset, typename UStorageProviderType> requires StorageProvider<UStorageProviderType, ((UBitSize + UBitOffset + 7) >> 3)>
    explicit operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UStorageProviderType>() const;

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
        // TODO: Implement friend std::istream& operator>>(std::istream& is, ArbitrarySignedInt& value)
        throw std::runtime_error("friend std::istream& operator>>(std::istream& is, ArbitrarySignedInt& value) not implemented.");
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
    ArbitrarySignedInt ReverseBytes() const;

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
    // Helper functions
    void Normalize(); // Ensure proper sign extension
    void SignExtend(); // Extend sign bit to unused bits
};

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> Abs(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& value);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> Gcd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> Lcm(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool>
CarryingAdd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> BorrowingSub(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize * 2, BitOffset, StorageProviderType> WideningLcm(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize * 2, BitOffset, StorageProviderType> WideningMul(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& b);

// Utility type aliases for common formats
template<typename StorageProvider>
using Int8 = ArbitrarySignedInt<8, 0, StorageProvider>;

template<typename StorageProvider>
using Int16 = ArbitrarySignedInt<16, 0, StorageProvider>;

template<typename StorageProvider>
using Int32 = ArbitrarySignedInt<32, 0, StorageProvider>;

template<typename StorageProvider>
using Int64 = ArbitrarySignedInt<64, 0, StorageProvider>;

template<typename StorageProvider>
using Int128 = ArbitrarySignedInt<128, 0, StorageProvider>;

template<typename StorageProvider>
using Int256 = ArbitrarySignedInt<256, 0, StorageProvider>;

#include "core/signed-int/impl/ArbitrarySignedIntImpl.h"

#endif //ARBITRARYSIGNEDINT_H
