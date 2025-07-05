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

#include "../../concepts/StorageProvider.h"

// Forward declaration - don't include the header
template<size_t BitSize, size_t BitOffset, typename StorageProviderType>
class ArbitrarySignedInt;

/**
 * @brief Represents an arbitrary-sized unsigned integer with customizable size, offset, and memory location.
 *
 * This class provides a comprehensive set of operations for arbitrary-sized unsigned integers,
 * including arithmetic, bitwise, comparison, utility, and conversion functions.
 * The size and memory layout of the integer are configurable via template parameters.
 *
 * @tparam BitSize The number of bits used to store the integer. It must be greater than 1.
 * @tparam BitOffset The bit offset for memory alignment.
 * @tparam StorageProvider The underlying storage provider.
 */
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
class ArbitraryUnsignedInt {
    static constexpr size_t storageBytes = (BitSize + BitOffset + 7) >> 3;
    using StorageType = typename StorageProviderType::template StorageType<storageBytes>;
    StorageType storage_;
    
    // Helper functions for arithmetic
    void Normalize(); // Ensure unused bits are zero
public:
    // Constructors
    ArbitraryUnsignedInt() : storage_() {
        storage_.Clear();
    }
    ArbitraryUnsignedInt(const ArbitraryUnsignedInt& other) = default;
    ArbitraryUnsignedInt(ArbitraryUnsignedInt&& other) = default;

    // Constructor from integral types
    template<typename T, typename = std::enable_if_t<std::is_integral_v<T> > >
    ArbitraryUnsignedInt(T value);

    // Constructor from string (binary, hex, or decimal)
    ArbitraryUnsignedInt(const char* str, int base = 10) 
        : ArbitraryUnsignedInt(std::string(str), base)  // ← Correct delegating constructor
    {
        // Body can be empty
    }
    ArbitraryUnsignedInt(const std::string& str, int base = 10);

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
    template<size_t NewBitSize, size_t NewBitOffset, typename NewStorageProvider>
    explicit operator ArbitraryUnsignedInt<NewBitSize, NewBitOffset, NewStorageProvider>() const;

    // Arithmetic operators
    ArbitraryUnsignedInt operator+(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt operator-(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt operator*(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt operator/(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt operator%(const ArbitraryUnsignedInt& other);

    // Assignment arithmetic operators
    ArbitraryUnsignedInt& operator+=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator-=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator*=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator/=(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt& operator%=(const ArbitraryUnsignedInt& other);

    // Bitwise operators
    ArbitraryUnsignedInt operator&(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt operator|(const ArbitraryUnsignedInt& other);
    ArbitraryUnsignedInt operator^(const ArbitraryUnsignedInt& other);
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
    ArbitraryUnsignedInt ReverseBytes() const;

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
};

// Additional utility functions
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>
Gcd(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>
Lcm(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b);

// Wide multiplication (returns result in double-wide type)
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType>
WideningMul(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType>
WideningLcm(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> CarryingAdd(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry);

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> BorrowingSub(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow);

// Utility type aliases for common formats
template<typename StorageProvider>
using UInt8 = ArbitraryUnsignedInt<8, 0, StorageProvider>;

template<typename StorageProvider>
using UInt16 = ArbitraryUnsignedInt<16, 0, StorageProvider>;

template<typename StorageProvider>
using UInt32 = ArbitraryUnsignedInt<32, 0, StorageProvider>;

template<typename StorageProvider>
using UInt64 = ArbitraryUnsignedInt<64, 0, StorageProvider>;

template<typename StorageProvider>
using UInt128 = ArbitraryUnsignedInt<128, 0, StorageProvider>;

template<typename StorageProvider>
using UInt256 = ArbitraryUnsignedInt<256, 0, StorageProvider>;

#include <core/unsigned-int/impl/ArbitraryUnsignedIntImpl.h>

#endif //ARBITRARYUNSIGNEDINT_H
