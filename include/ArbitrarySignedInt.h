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

#include "../include/concepts/StorageProvider.h"
#include "ArbitraryUnsignedInt.h"
#include "../cmake-build-release/_deps/googletest-src/googletest/include/gtest/internal/gtest-internal.h"

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
    template<size_t NewBitSize, size_t NewBitOffset, typename NewStorageProviderType>
    explicit operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewStorageProviderType>() const;

    // Conversion to/from unsigned
    template<size_t UBitSize, size_t UBitOffset, typename UStorageProviderType>
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

// == CONSTRUCTORS ==
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T, typename>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ArbitrarySignedInt(T value) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    storage_.Clear();

    // bit cast the T
    using UnsignedT = std::make_unsigned_t<T>;
    UnsignedT bits = std::bit_cast<UnsignedT>(value);

    // truncate it
    if constexpr (BitSize < sizeof(T) * 8) {
        constexpr UnsignedT mask = (1ULL << BitSize) - 1;
        bits &= mask;
    }

    // Use IByteCopyable interface for efficient storage operations
    const uint8_t* byte_data = std::bit_cast<const uint8_t*>(&bits);
    // Round up to bytes
    size_t byte_count = std::min(sizeof(bits), (BitSize + 7) / 8);

    storage_.CopyFromBytes(byte_data,
        sizeof(bits),
        0,
        // srcStart
        BitOffset / 8,
        // dstStart (convert bit offset to byte offset)
        byte_count); // copyCount
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ArbitrarySignedInt(const std::string& str, int base) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ArbitrarySignedInt(const std::string& str, int base)
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ArbitrarySignedInt(const std::string& str, int base) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T, typename>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator=(T value) {
    // Create temporary and move-assign
    *this = ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>(value);
    return *this;
}

// == TYPE CONVERTERS ==
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator bool() const {
    return this->storage_;
}

// == SIGNED INTEGER TYPE CONVERT == 
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator char() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator char() const
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator char() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator short() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator short() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator short() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator int() const {
    int result = 0;
    for (size_t i = 0; i < BitSize && i < sizeof(int) * 8; ++i) {
        if (storage_.GetBit(i)) {
            result |= (1 << i);
        }
    }
    if (IsNegative()) {
        return -result;
    }
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long long() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long long() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator long long() not implemented.");
}

// == UNSIGNED INTEGER TYPE CONVERT ==
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned char() const {
    return storage_[0];
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned short() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned short() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned short() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned int() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned int() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned int() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long long() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long long() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long long() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<size_t NewBitSize, size_t NewBitOffset, typename NewStorageProvider>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewStorageProvider>() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewStorageProvider>() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitrarySignedInt<NewBitSize, NewBitOffset, NewStorageProvider>() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<size_t UBitSize, size_t UBitOffset, typename UStorageProvider>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UStorageProvider>() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UStorageProvider>() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitraryUnsignedInt<UBitSize, UBitOffset, UStorageProvider>() not implemented.");
}

// == ARITHMETIC OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%(const ArbitrarySignedInt& other) not implemented.");
}

// == UNARY ARITHMETIC OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-() const {
    return this->operator~()++;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+() const {
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator++() {
    storage_.Increment();
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator++(int) {
    ArbitrarySignedInt temp = *this;
    storage_.Increment();
    return temp;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator--() {
    storage_.Decrement();
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator--(int) {
    ArbitrarySignedInt temp = *this;
    storage_.Decrement();
    return temp;
}

// == ARITHMETIC ASSIGN OPERATIONS == 
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator+=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator-=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator*=(const ArbitrarySignedInt& other) not implemented.");   
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator/=(const ArbitrarySignedInt& other) not implemented.");  
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%=(const ArbitrarySignedInt& other) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator%=(const ArbitrarySignedInt& other) not implemented.");  
}

// == BITWISE OPERATIONS ==

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
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator~() const {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.BitwiseNot();
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

// == BITWISE ASSIGN OPERATIONS ==

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

// == COMPARISON OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator==(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator==(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator==(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator!=(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator!=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator!=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator<=(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>=(const ArbitrarySignedInt& other) const {
    // TODO: Implement bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>=(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::operator>=(const ArbitrarySignedInt& other) not implemented.");  
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::GetBit(size_t index) const {
    return storage_.GetBit(index);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SetBit(size_t index) {
    storage_.SetBit(index);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ClearBit(size_t index) {
    storage_.ClearBit(index);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FlipBit(size_t index) {
    storage_.FlipBit(index);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::IsNegative() const {
    return storage_.GetBit(BitSize - 1);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::IsPositive() const {
    return !storage_.GetBit(BitSize - 1) && !storage_.IsZero();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Abs() const {
    this->storage_.ClearBit(BitSize - 1);
    return *this;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
int ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Sign() const {
    if (storage_.IsZero()) {
        return 0;
    }
    return storage_.GetBit(BitSize - 1) ?
               -1 :
               1;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CountLeadingZeros() const {
    return storage_.CountLeadingZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CountTrailingZeros() const {
    return storage_.CountTrailingZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::PopCount() const {
    return storage_.PopCount();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToString(int base) const {
    if (storage_.IsAllZeros()) {
        return "0";
    }

    std::string result;
    bool is_negative = IsNegative();
    auto temp_storage = storage_;

    if (is_negative) {
        // Convert to positive for easier processing
        temp_storage.BitwiseNot();
        temp_storage.Increment();
    }

    auto temp_storage_clone = temp_storage.Clone();
    while (!temp_storage_clone->IsAllZeros()) {
        int remainder = 0;
        auto new_storage = temp_storage.Clone();
        new_storage->ClearAllBits();
        for (size_t i = temp_storage_clone->GetBitSize(); i > 0; --i) {
            remainder <<= 1;
            if (temp_storage_clone->GetBit(i - 1)) {
                remainder |= 1;
            }
            if (remainder >= base) {
                new_storage->SetBit(i - 1);
                remainder -= base;
            }
        }
        result += "0123456789abcdef"[remainder];
        temp_storage_clone = std::move(new_storage);
    }

    if (is_negative) {
        result += "-";
    }

    std::ranges::reverse(result);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() const {
    // TODO: Implement std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() not implemented."); 
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() const {
    // TODO: Implement std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() const {
    // TODO: Implement std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() not implemented."); 
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Max() {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> max;
    max.storage_.SetAllBits();
    return max;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::Min() {
    ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> max;
    max.storage_.ClearAllBits();
    return max;
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
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAdd(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedAdd(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAdd(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedSub(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedSub(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedSub(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedMul(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedMul(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedMul(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedDiv(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedDiv(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedDiv(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedRem(const ArbitrarySignedInt& other) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedRem(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedRem(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNeg() const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedNeg() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNeg() not implemented."); 
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAbs() const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedAbs() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAbs() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPow(const ArbitrarySignedInt& exp) const {
    // TODO: Implement std::optional<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> > CheckedPow(const ArbitrarySignedInt& exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPow(const ArbitrarySignedInt& exp) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAdd(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAdd(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAdd(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingSub(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingSub(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingSub(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAbs() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAbs() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAbs() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingNeg() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingNeg() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingNeg() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitrarySignedInt& exp) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitrarySignedInt& exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitrarySignedInt& exp) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingAdd(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingAdd(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingAdd(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingSub(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingSub(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingSub(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingMul(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingMul(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingMul(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingDiv(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingDiv(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingDiv(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingRem(const ArbitrarySignedInt& other) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingRem(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingRem(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingNeg() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingNeg() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingNeg() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingAbs() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingAbs() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingAbs() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingPow(const ArbitrarySignedInt& exp) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingPow(const ArbitrarySignedInt& exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingPow(const ArbitrarySignedInt& exp) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingAdd(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingAdd(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingAdd(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingSub(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingSub(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingSub(const ArbitrarySignedInt& other) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingMul(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingMul(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingMul(const ArbitrarySignedInt& other) not implemented.");   
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingDiv(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingDiv(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingDiv(const ArbitrarySignedInt& other) not implemented.");  
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingRem(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& other) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingRem(const ArbitrarySignedInt& other) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingRem(const ArbitrarySignedInt& other) not implemented."); 
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingNeg() {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingNeg() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingNeg() not implemented."); 
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingAbs() {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingAbs() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingAbs() not implemented."); 
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingPow(const ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>& exp) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingPow(const ArbitrarySignedInt& exp) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingPow(const ArbitrarySignedInt& exp) not implemented."); 
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingShl(size_t shift) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingShl(size_t shift) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShl(size_t shift) not implemented."); 
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingShr(size_t shift) {
    // TODO: Implement std::pair<ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>, bool> OverflowingShr(size_t shift) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShr(size_t shift) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CountOnes() const {
    return storage_.CountOnes();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::CountZeros() const {
    return storage_.CountZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::LeadingZeros() const {
    return storage_.LeadingZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::TrailingZeros() const {
    return storage_.TrailingZeros();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::LeadingOnes() const {
    return storage_.LeadingOnes();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::TrailingOnes() const {
    return storage_.TrailingOnes();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::RotateLeft(size_t n) const {
    return storage_.RotateLeft(n);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::RotateRight(size_t n) const {
    return storage_.RotateRight(n);
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBits() const {
    return storage_.ReverseBits();
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::IsZero() const {
    return storage_.IsAllZeros();
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
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToBeBytes() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBeBytes() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToLeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToLeBytes() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToLeBytes() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToNeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ToNeBytes() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToNeBytes() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType> ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented."); 
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

#endif //ARBITRARYSIGNEDINT_H
