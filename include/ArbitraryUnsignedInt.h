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
#include "../include/concepts/StorageProvider.h"
#include "storage/CPUStorage.h"

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

// == CONSTRUCTORS == 

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T, typename>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ArbitraryUnsignedInt(T value) : storage_() {
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

    if constexpr (std::endian::native == std::endian::big) {
        // Reverse bytes if native endian is big
        storage_.ReverseBytes();
    }
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ArbitraryUnsignedInt(const std::string& str, int base) {
    if (base < 2 || base > 36) {
        throw std::invalid_argument("Invalid base");
    }
    // Clear the storage first
    storage_.Clear();

    // Convert base to ArbitraryUnsignedInt
    ArbitraryUnsignedInt base_value(base);

    for (char c : str) {
        if ('0' <= c && c <= '9') {
            c -= '0';
        }
        else if ('a' <= c && c <= 'z') {
            c -= 'a' - 10;
        }
        else if ('A' <= c && c <= 'Z') {
            c -= 'A' - 10;
        }
        else {
            throw std::invalid_argument("Invalid character in string");
        }
        if (c >= base) {
            throw std::invalid_argument("Invalid character in string");
        }
        this->operator*=(base_value); // Now using ArbitraryUnsignedInt
        this->operator+=(ArbitraryUnsignedInt(c)); // Convert digit to ArbitraryUnsignedInt
    }
    this->Normalize();
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T, typename>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator=(T value) {
    // Create temporary and move-assign
    *this = ArbitraryUnsignedInt(value);
    return *this;
}

// == TYPE CONVERSION ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator bool() const {
    return not this->storage_.IsZero();
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned char() const {
    unsigned char result = 0;
    size_t byteOffset = BitOffset / 8;
    size_t bitOffset = BitOffset % 8;
    result |= storage_[byteOffset] >> bitOffset;
    if (storage_.GetByteSize() > 1 + byteOffset && BitSize >= 8 - bitOffset) {
        result |= storage_[1 + byteOffset] << (8 - bitOffset);
    }
    if (BitSize < 8) {
        result &= (1 << BitSize) - 1;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned short() const {
    unsigned short result = 0;
    size_t target_byte_size = sizeof(result);
    for (int i = 0; i < std::min(target_byte_size, storage_.GetByteSize()); i++) {
        result |= storage_[i];
        result <<= 8;
    }
    result >>= BitOffset;
    if (storage_.GetByteSize() > target_byte_size && BitSize >= 8 - BitOffset) {
        result |= storage_[target_byte_size] << (8 - BitOffset);
    }
    if (BitSize < 8 * target_byte_size) {
        result &= (1ULL << BitSize) - 1;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned int() const {
    unsigned int result = 0;
    size_t target_byte_size = sizeof(result);
    result = storage_[0] >> BitOffset;
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long() const {
    unsigned long result = 0;
    size_t target_byte_size = sizeof(result);
    result = storage_[0] >> BitOffset;
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator unsigned long long() const {
    unsigned long long result = 0;
    size_t target_byte_size = sizeof(result);
    result = storage_[0] >> BitOffset;
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<size_t NewBitSize, size_t NewBitOffset, typename NewStorageProvider>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator ArbitraryUnsignedInt<NewBitSize, NewBitOffset, NewStorageProvider>() const {
    auto result = ArbitraryUnsignedInt<NewBitSize, NewBitOffset, NewStorageProvider>();
    result.storage_.CopyBitsFrom(storage_, BitOffset, std::min(BitSize, NewBitSize));
    return result;
}

// == ARITHMETIC OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator+(const ArbitraryUnsignedInt& other) {
    for (size_t i = 0; i < storage_.GetByteSize(); i++) {
        storage_[i] += other.storage_[i];
        if (storage_[i] < other.storage_[i] and i + 1 < storage_.GetByteSize()) {
            storage_[i + 1] += 1;
        }
    }
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator-(const ArbitraryUnsignedInt& other) {
    bool shouldBorrow = false;
    for (size_t i = 0; i < storage_.GetByteSize(); i++) {
        if (storage_[i] < other.storage_[i]) {
            shouldBorrow = true;
        }
        else {
            shouldBorrow = false;
        }
        storage_[i] += other.storage_[i];
        if (shouldBorrow and i + 1 < storage_.GetByteSize()) {
            storage_[i + 1] -= 1;
        }
    }
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator*(const ArbitraryUnsignedInt& other) {
    ArbitraryUnsignedInt result;
    ArbitraryUnsignedInt multiplicand = *this;
    ArbitraryUnsignedInt multiplier = other;

    // Handle zero cases
    if (multiplicand.IsZero() || multiplier.IsZero()) {
        return result;
    }

    size_t bitShiftCount = BitSize;
    // Standard binary multiplication algorithm
    while (bitShiftCount) {
        if (multiplier.GetBit(0)) {  // If lowest bit is 1
            result += multiplicand;
        }
        multiplicand <<= 1;  // Shift multiplicand left
        multiplier >>= 1;    // Shift multiplier right
        bitShiftCount -= 1;
    }

    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator/(const ArbitraryUnsignedInt& other) {
    // Division by zero check
    if (other.IsZero()) {
        throw std::runtime_error("Division by zero");
    }

    ArbitraryUnsignedInt quotient;

    // Handle zero dividend
    if (this->IsZero()) {
        return quotient;
    }

    // Handle division by 1 (all zeros except LSB)
    ArbitraryUnsignedInt one;
    one.storage_.ClearAllBits();
    one.SetBit(0);
    if (other == one) {
        return *this;
    }

    // Long division algorithm using bit operations
    ArbitraryUnsignedInt dividend = *this;
    ArbitraryUnsignedInt divisor = other;

    // Find the position of the most significant bit in divisor
    size_t divisor_msb = 0;
    for (size_t i = BitSize; i > 0; --i) {
        if (divisor.GetBit(i - 1)) {
            divisor_msb = i - 1;
            break;
        }
    }

    // Find the position of the most significant bit in dividend
    size_t dividend_msb = 0;
    for (size_t i = BitSize; i > 0; --i) {
        if (dividend.GetBit(i - 1)) {
            dividend_msb = i - 1;
            break;
        }
    }

    if (dividend_msb < divisor_msb) {
        return quotient; // Result is 0
    }

    // Shift divisor to align with dividend's MSB
    size_t shift = dividend_msb - divisor_msb;
    divisor.storage_.ShiftLeft(shift);

    for (size_t i = 0; i <= shift; ++i) {
        // Compare dividend with shifted divisor
        bool can_subtract = true;

        for (size_t bit = BitSize; bit > 0; --bit) {
            bool div_bit = dividend.GetBit(bit - 1);
            bool divisor_bit = divisor.GetBit(bit - 1);

            if (div_bit != divisor_bit) {
                can_subtract = div_bit;
                break;
            }
        }

        if (can_subtract) {
            // Subtract divisor from dividend using bit operations
            bool borrow = false;
            for (size_t bit = 0; bit < BitSize; ++bit) {
                bool a = dividend.GetBit(bit);
                bool b = divisor.GetBit(bit);

                bool diff = a ^ b ^ borrow;
                borrow = (!a && b) || (!a && borrow) || (b && borrow);

                dividend.SetBit(bit, diff);
            }

            // Set corresponding bit in quotient
            quotient.SetBit(shift - i);
        }

        // Shift divisor right for next iteration
        if (i < shift) {
            divisor.storage_.ShiftRight(1);
        }
    }

    return quotient;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator%(const ArbitraryUnsignedInt& other) {
    // Division by zero check
    if (other.IsZero()) {
        throw std::runtime_error("Division by zero");
    }

    // Handle zero dividend
    if (this->IsZero()) {
        ArbitraryUnsignedInt result;
        return result;
    }

    // Handle modulo by 1
    ArbitraryUnsignedInt one;
    one.storage_.ClearAllBits();
    one.SetBit(0);
    if (other == one) {
        ArbitraryUnsignedInt result;
        result.storage_.ClearAllBits();
        return result;
    }

    // Use the same long division algorithm as division,
    // but return the remainder instead of quotient
    ArbitraryUnsignedInt remainder = *this;
    ArbitraryUnsignedInt divisor = other;

    // Find MSB positions
    size_t divisor_msb = 0;
    for (size_t i = BitSize; i > 0; --i) {
        if (divisor.GetBit(i - 1)) {
            divisor_msb = i - 1;
            break;
        }
    }

    size_t remainder_msb = 0;
    for (size_t i = BitSize; i > 0; --i) {
        if (remainder.GetBit(i - 1)) {
            remainder_msb = i - 1;
            break;
        }
    }

    if (remainder_msb < divisor_msb) {
        return remainder;
    }

    // Shift divisor to align with remainder's MSB
    size_t shift = remainder_msb - divisor_msb;
    divisor.storage_.ShiftLeft(shift);

    for (size_t i = 0; i <= shift; ++i) {
        // Compare remainder with shifted divisor
        bool can_subtract = true;

        for (size_t bit = BitSize; bit > 0; --bit) {
            bool rem_bit = remainder.GetBit(bit - 1);
            bool divisor_bit = divisor.GetBit(bit - 1);

            if (rem_bit != divisor_bit) {
                can_subtract = rem_bit;
                break;
            }
        }

        if (can_subtract) {
            // Subtract divisor from remainder
            bool borrow = false;
            for (size_t bit = 0; bit < BitSize; ++bit) {
                bool a = remainder.GetBit(bit);
                bool b = divisor.GetBit(bit);

                bool diff = a ^ b ^ borrow;
                borrow = (!a && b) || (!a && borrow) || (b && borrow);

                remainder.SetBit(bit, diff);
            }
        }

        // Shift divisor right for next iteration
        if (i < shift) {
            divisor.storage_.ShiftRight(1);
        }
    }

    return remainder;
}

// == ARITHMETIC ASSIGNMENT OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator+=(const ArbitraryUnsignedInt& other) {
    *this = *this + other;
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator-=(const ArbitraryUnsignedInt& other) {
    *this = *this - other;
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator*=(const ArbitraryUnsignedInt& other) {
    *this = *this * other;
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator/=(const ArbitraryUnsignedInt& other) {
    *this = *this / other;
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator%=(const ArbitraryUnsignedInt& other) {
    *this = *this % other;
    return *this;
}

// == BITWISE OPERATION ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator&(const ArbitraryUnsignedInt& other) {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = storage_;
    result.storage_.ByteAnd(other.storage_);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator|(const ArbitraryUnsignedInt& other) {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = storage_;
    result.storage_.ByteOr(other.storage_);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator^(const ArbitraryUnsignedInt& other) {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = storage_;
    result.storage_.ByteXor(other.storage_);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator~() const {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = storage_.ByteNot();
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator<<(size_t shift) const {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.ShiftLeft(shift);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator>>(size_t shift) const {
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> result;
    result.storage_ = this->storage_;
    result.storage_.ShiftRight(shift);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator&=(const ArbitraryUnsignedInt& other) {
    this->storage_.BitwiseAnd(other->storage_);
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator|=(const ArbitraryUnsignedInt& other) {
    this->storage_.BitwiseOr(other->storage_);
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator^=(const ArbitraryUnsignedInt& other) {
    this->storage_.BitwiseXor(other->storage_);
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator<<=(size_t shift) {
    this->storage_.ShiftLeft(shift);
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator>>=(size_t shift) {
    this->storage_.ShiftRight(shift);
    return *this;
}

// == COMPARISON OPERATOR ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator==(const ArbitraryUnsignedInt& other) const {
    const int rightOffset = 8 - ((BitSize + BitOffset) & 7);
    for (int i = storage_.GetByteSize() - 1; i >= 0; --i) {
        int leftByte = storage_[i];
        int rightByte = other.storage_[i];
        if (i == storage_.GetByteSize() - 1) {
            leftByte = (1ULL << rightOffset) - 1;
            rightByte = (1ULL << rightOffset) - 1;
        }
        else if (i == 0) {
            leftByte <<= BitOffset;
            rightByte <<= BitOffset;
        }
        if (leftByte != rightByte) {
            return false;
        }
    }
    return true;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator!=(const ArbitraryUnsignedInt& other) const {
    const int rightOffset = 8 - ((BitSize + BitOffset) & 7);
    for (int i = storage_.GetByteSize() - 1; i >= 0; --i) {
        int leftByte = storage_[i];
        int rightByte = other.storage_[i];
        if (i == storage_.GetByteSize() - 1) {
            leftByte = (1ULL << rightOffset) - 1;
            rightByte = (1ULL << rightOffset) - 1;
        }
        else if (i == 0) {
            leftByte <<= BitOffset;
            rightByte <<= BitOffset;
        }
        if (leftByte == rightByte) {
            return false;
        }
    }
    return true;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator<(const ArbitraryUnsignedInt& other) const {
    const int rightOffset = 8 - ((BitSize + BitOffset) & 7);
    for (int i = storage_.GetByteSize() - 1; i >= 0; --i) {
        int leftByte = storage_[i];
        int rightByte = other.storage_[i];
        if (i == storage_.GetByteSize() - 1) {
            leftByte = (1ULL << rightOffset) - 1;
            rightByte = (1ULL << rightOffset) - 1;
        }
        else if (i == 0) {
            leftByte <<= BitOffset;
            rightByte <<= BitOffset;
        }
        if (leftByte >= rightByte) {
            return false;
        }
    }
    return true;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator<=(const ArbitraryUnsignedInt& other) const {
    const int rightOffset = 8 - ((BitSize + BitOffset) & 7);
    for (int i = storage_.GetByteSize() - 1; i >= 0; --i) {
        int leftByte = storage_[i];
        int rightByte = other.storage_[i];
        if (i == storage_.GetByteSize() - 1) {
            leftByte = (1ULL << rightOffset) - 1;
            rightByte = (1ULL << rightOffset) - 1;
        }
        else if (i == 0) {
            leftByte <<= BitOffset;
            rightByte <<= BitOffset;
        }
        if (leftByte > rightByte) {
            return false;
        }
    }
    return true;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator>(const ArbitraryUnsignedInt& other) const {
    const int rightOffset = 8 - ((BitSize + BitOffset) & 7);
    for (int i = storage_.GetByteSize() - 1; i >= 0; --i) {
        int leftByte = storage_[i];
        int rightByte = other.storage_[i];
        if (i == storage_.GetByteSize() - 1) {
            leftByte = (1ULL << rightOffset) - 1;
            rightByte = (1ULL << rightOffset) - 1;
        }
        else if (i == 0) {
            leftByte <<= BitOffset;
            rightByte <<= BitOffset;
        }
        if (leftByte <= rightByte) {
            return false;
        }
    }
    return true;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator>=(const ArbitraryUnsignedInt& other) const {
    const int rightOffset = 8 - ((BitSize + BitOffset) & 7);
    for (int i = storage_.GetByteSize() - 1; i >= 0; --i) {
        int leftByte = storage_[i];
        int rightByte = other.storage_[i];
        if (i == storage_.GetByteSize() - 1) {
            leftByte = (1ULL << rightOffset) - 1;
            rightByte = (1ULL << rightOffset) - 1;
        }
        else if (i == 0) {
            leftByte <<= BitOffset;
            rightByte <<= BitOffset;
        }
        if (leftByte < rightByte) {
            return false;
        }
    }
    return true;
}

// == INCREMENT & DECREMENT OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator++() {
    storage_.Increment();
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator++(int) {
    ArbitraryUnsignedInt temp = *this;
    storage_.Increment();
    return temp;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator--() {
    storage_.Decrement();
    return *this;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator--(int) {
    ArbitraryUnsignedInt temp = *this;
    storage_.Decrement();
    return temp;
}

// == BITWISE ACCESS OPERATORS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::GetBit(size_t index) const {
    return storage_.GetBit(index + BitOffset);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SetBit(size_t index, bool value) {
    storage_.SetBit(index + BitOffset, value);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ClearBit(size_t index) {
    storage_.ClearBit(index + BitOffset);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FlipBit(size_t index) {
    storage_.FlipBit(index + BitOffset);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountLeadingZeros() const {
    storage_.CountLeadingZeros();
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountTrailingZeros() const {
    storage_.CountTrailingZeros();
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::PopCount() const {
    storage_.PopCount();
}

// == STRINGIFY OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToString(int base) const {
    // TODO: Implement std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToString(int base) const
    throw std::runtime_error("std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToString(int base) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() const {
    // TODO: Implement std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() const
    throw std::runtime_error("std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() const {
    // TODO: Implement std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() const
    throw std::runtime_error("std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() const {
    // TODO: Implement std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() const
    throw std::runtime_error("std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() const not implemented.");
}

// == STATIC PROPERTIES ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Max() {
    auto result = ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>();
    result.storage_.SetAllBits();
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Min() {
    auto result = ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>();
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> >
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::DivRem(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::DivRem(const ArbitraryUnsignedInt& other) const
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::DivRem(const ArbitraryUnsignedInt& other) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Pow(const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Pow(const ArbitraryUnsignedInt& exp) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Pow(const ArbitraryUnsignedInt& exp) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Pow(size_t exp) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Pow(size_t exp) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Pow(size_t exp) const not implemented.");
}

// == CHECKED OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedAdd(const ArbitraryUnsignedInt& other) const {
    auto result = *this + other;
    if (result > *this || result > other) {
        return std::nullopt;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedSub(const ArbitraryUnsignedInt& other) const {
    auto result = *this - other;
    if (*this < other) {
        return std::nullopt;
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedMul(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedMul(const ArbitraryUnsignedInt& other) const
    throw std::runtime_error("std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedMul(const ArbitraryUnsignedInt& other) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedDiv(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedDiv(const ArbitraryUnsignedInt& other) const
    throw std::runtime_error("std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedDiv(const ArbitraryUnsignedInt& other) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedRem(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedRem(const ArbitraryUnsignedInt& other) const
    throw std::runtime_error("std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedRem(const ArbitraryUnsignedInt& other) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPow(const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPow(const ArbitraryUnsignedInt& exp) const
    throw std::runtime_error("std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPow(const ArbitraryUnsignedInt& exp) const not implemented.");
}

// == SATURATING OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingAdd(const ArbitraryUnsignedInt& other) const {
    auto result = *this + other;
    if (result > *this || result > other) {
        return ArbitraryUnsignedInt::Max();
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingSub(const ArbitraryUnsignedInt& other) const {
    auto result = *this - other;
    if (*this < other) {
        return ArbitraryUnsignedInt::Min();
    }
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitraryUnsignedInt& other) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingMul(const ArbitraryUnsignedInt& other) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitraryUnsignedInt& exp) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::SaturatingPow(const ArbitraryUnsignedInt& exp) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingAdd(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this + other.
    return *this + other;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingSub(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this - other.
    return *this - other;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingMul(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this * other.
    return *this * other;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingDiv(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this / other.
    return *this / other;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingRem(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this % other.
    return *this % other;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingPow(const ArbitraryUnsignedInt& exp) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns pow(this, other).
    return pow(*this, exp);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) not implemented.");
}

// == OVERFLOWING OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingAdd(const ArbitraryUnsignedInt& other) const {
    auto result = *this + other;
    if (result > *this || result > other) {
        return { result, true };
    }
    return { result, false };
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingSub(const ArbitraryUnsignedInt& other) const {
    auto result = *this - other;
    if (*this < other) {
        return { result, true };
    }
    return { result, false };
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingMul(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingMul(const ArbitraryUnsignedInt& other) const
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingMul(const ArbitraryUnsignedInt& other) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingDiv(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingDiv(const ArbitraryUnsignedInt& other) const
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingDiv(const ArbitraryUnsignedInt& other) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingRem(const ArbitraryUnsignedInt& other) const {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingRem(const ArbitraryUnsignedInt& other) const
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingRem(const ArbitraryUnsignedInt& other) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingPow(const ArbitraryUnsignedInt& exp) const {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingPow(const ArbitraryUnsignedInt& exp) const
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingPow(const ArbitraryUnsignedInt& exp) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShl(size_t shift) const {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShl(size_t shift) const
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShl(size_t shift) const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShr(size_t shift) const {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShr(size_t shift) const
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::OverflowingShr(size_t shift) const not implemented.");
}

// == BITWISE COUNTING OPERATIONS ==

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountOnes() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountOnes() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountOnes() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountZeros() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountZeros() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CountZeros() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingZeros() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingZeros() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingZeros() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingZeros() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingZeros() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingZeros() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingOnes() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingOnes() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::LeadingOnes() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingOnes() const {
    // TODO: Implement size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingOnes() const
    throw std::runtime_error("size_t ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TrailingOnes() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateLeft(size_t n) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateLeft(size_t n) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateLeft(size_t n) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateRight(size_t n) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateRight(size_t n) not implemented.
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::RotateRight(size_t n) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBits() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBits() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBits() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ReverseBytes() not implemented.");
}

// == UTILITY OPERATIONS

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::IsZero() const {
    const int rightOffset = 8 - ((BitSize + BitOffset) & 7);
    for (int i = storage_.GetByteSize() - 1; i >= 0; --i) {
        int leftByte = storage_[i];
        if (i == storage_.GetByteSize() - 1) {
            leftByte = (1ULL << rightOffset) - 1;
        }
        else if (i == 0) {
            leftByte <<= BitOffset;
        }
        if (leftByte != 0) {
            return false;
        }
    }
    return true;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Signum() const {
    return IsZero() ?
               0 :
               1;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
template<typename T>
std::optional<T> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TryInto() const {
    // TODO: Implement std::optional<T> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TryInto() const
    throw std::runtime_error("std::optional<T> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::TryInto() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::NextPowerOfTwo() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNextPowerOfTwo() const {
    // TODO: Implement std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNextPowerOfTwo() const
    throw std::runtime_error("std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedNextPowerOfTwo() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::PreviousPowerOfTwo() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPreviousPowerOfTwo() const {
    // TODO: Implement std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPreviousPowerOfTwo() const
    throw std::runtime_error("std::optional<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> > ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::CheckedPreviousPowerOfTwo() const not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::IsPowerOfTwo() const {
    // TODO: Implement bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::IsPowerOfTwo() const
    throw std::runtime_error("bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::IsPowerOfTwo() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToBeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToBeBytes() const
    throw std::runtime_error("std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToBeBytes() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToLeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToLeBytes() const
    throw std::runtime_error("std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToLeBytes() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToNeBytes() const {
    // TODO: Implement std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToNeBytes() const
    throw std::runtime_error("std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToNeBytes() not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes)
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes)
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes)
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((BitSize + BitOffset + 7) >> 3)>& bytes) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Normalize() {
    // TODO: Implement void ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::Normalize()
    return;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> Gcd(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    // This code is based on euclid's algorithm, which states 
    // WLOG, gcd(a, b) = gcd(a % b, b)
    // So, we can just call the recursive function.
    if (a < b) {
        return Gcd(b, a);
    }
    return b.IsZero() ?
               a :
               Gcd(b, a % b);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> Lcm(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    return a * b / Gcd(a, b);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType> WideningMul(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    // TODO: Implement ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProvider> WideningMul(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b)
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProvider>::WideningMul(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize * 2, BitOffset, StorageProviderType> WideningLcm(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b) {
    return WideningMul(a, b / Gcd(a, b));
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> CarryingAdd(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry) {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> CarryingAdd(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry)
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> CarryingAdd(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool carry) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> BorrowingSub(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow) {
    // TODO: Implement std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> BorrowingSub(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow)
    throw std::runtime_error("std::pair<ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>, bool> BorrowingSub(const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& a, const ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>& b, bool borrow) not implemented.");
}

#endif //ARBITRARYUNSIGNEDINT_H
