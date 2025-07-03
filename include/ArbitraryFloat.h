//
// Created by Lumi on 25. 6. 15.
//

#ifndef ARBITRARYFLOAT_H
#define ARBITRARYFLOAT_H
#include <iostream>
#include <string>
#include <utility>
#include <type_traits>
#include <array>
#include <optional>
#include <cstdint>

#include "ArbitrarySignedInt.h"
#include "ArbitraryUnsignedInt.h"
#include "../include/concepts/StorageProvider.h"

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
/**
 * Represents an arbitrary-precision floating point number with customizable
 * exponent and mantissa sizes. Provides support for IEEE 754 special values.
 * Includes a variety of operators, conversion functions, math functions,
 * rounding functions, and checked arithmetic.
 */
class ArbitraryFloat {
    static_assert(ExpBits > 1, "Exponent bits must be greater than 1.");
    static_assert(MantissaBits > 0, "Mantissa bits must be greater than 0.");
    static constexpr size_t totalBits = ExpBits + MantissaBits + 1;
    static constexpr size_t storageBytes = (totalBits + 7) >> 3;
    using StorageType = typename StorageProviderType::template StorageType<storageBytes>;
    StorageType storage_;
    
public:
    // ===== CONSTRUCTORS =====
    ArbitraryFloat() = default;
    ArbitraryFloat(const ArbitraryFloat& other) = default;
    ArbitraryFloat(ArbitraryFloat&& other) = default;

    // Constructor from built-in floating point types
    explicit ArbitraryFloat(float value);
    explicit ArbitraryFloat(double value);
    explicit ArbitraryFloat(long double value);

    // Constructor from integral types
    template<typename T, typename = std::enable_if_t<std::is_integral_v<T> > >
    explicit ArbitraryFloat(T value);

    // Constructor from string
    explicit ArbitraryFloat(const char* str)
        : ArbitraryFloat(std::string(str)) // ← Correct delegating constructor
    {
        // Body can be empty
    }
    explicit ArbitraryFloat(const std::string& str);

    // Constructor from arbitrary integers
    template<size_t BitSize, size_t BitOffset, typename IntStorageProvider>
    explicit ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider>& value);

    template<size_t BitSize, size_t BitOffset, typename IntStorageProvider>
    explicit ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider>& value);

    // ===== ASSIGNMENT OPERATORS =====
    ArbitraryFloat& operator=(const ArbitraryFloat& other) = default;
    ArbitraryFloat& operator=(ArbitraryFloat&& other) = default;

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T> > >
    ArbitraryFloat& operator=(T value);

    // ===== CONVERSION OPERATORS =====
    explicit operator float() const;
    explicit operator double() const;
    explicit operator long double() const;
    explicit operator long long() const;
    explicit operator unsigned long long() const;
    explicit operator int() const;
    explicit operator unsigned int() const;
    explicit operator short() const;
    explicit operator unsigned short() const;
    explicit operator char() const;
    explicit operator unsigned char() const;
    explicit operator bool() const;

    template<size_t NewExp, size_t NewMant, typename NewStorageProvider>
    explicit operator ArbitraryFloat<NewExp, NewMant, NewStorageProvider>() const;

    // ===== UNARY OPERATORS =====
    ArbitraryFloat operator+() const; // unary plus
    ArbitraryFloat operator-() const; // unary minus

    // ===== ARITHMETIC OPERATORS =====
    ArbitraryFloat operator+(const ArbitraryFloat& other) const;
    ArbitraryFloat operator-(const ArbitraryFloat& other) const;
    ArbitraryFloat operator*(const ArbitraryFloat& other) const;
    ArbitraryFloat operator/(const ArbitraryFloat& other) const;

    // ===== ASSIGNMENT ARITHMETIC OPERATORS =====
    ArbitraryFloat& operator+=(const ArbitraryFloat& other);
    ArbitraryFloat& operator-=(const ArbitraryFloat& other);
    ArbitraryFloat& operator*=(const ArbitraryFloat& other);
    ArbitraryFloat& operator/=(const ArbitraryFloat& other);

    // ===== COMPARISON OPERATORS =====
    bool operator==(const ArbitraryFloat& other) const;
    bool operator!=(const ArbitraryFloat& other) const;
    bool operator<(const ArbitraryFloat& other) const;
    bool operator<=(const ArbitraryFloat& other) const;
    bool operator>(const ArbitraryFloat& other) const;
    bool operator>=(const ArbitraryFloat& other) const;

    // ===== IEEE 754 SPECIAL VALUE QUERIES =====
    bool IsFinite() const;
    bool IsInf() const;
    bool IsNaN() const;
    bool IsNormal() const;
    bool IsSubnormal() const;
    bool IsZero() const;
    bool SignBit() const;

    // ===== VALUE CATEGORY FUNCTIONS =====
    bool IsPositive() const;
    bool IsNegative() const;
    int Sign() const; // returns -1, 0, or 1

    // ===== IEEE 754 COMPONENT ACCESS =====
    bool GetSignBit() const;
    void SetSignBit(bool sign);

    // Get exponent (raw and biased)
    template<size_t ExpSize = ExpBits, size_t ExpOffset = 0, typename ExpStorageProvider = StorageProviderType>
    ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpStorageProvider> GetRawExponent() const;

    template<size_t ExpSize = ExpBits + 1, size_t ExpOffset = 0, typename ExpStorageProvider = StorageProviderType>
    ArbitrarySignedInt<ExpSize, ExpOffset, ExpStorageProvider> GetExponent() const;

    // Get mantissa/significand
    template<size_t MantSize, size_t MantOffset = 0, typename MantStorageProvider = StorageProviderType>
    ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProvider> GetMantissa() const;

    template<size_t MantSize, size_t MantOffset = 0, typename MantStorageProvider = StorageProviderType>
    ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProvider> GetSignificand() const;

    // ===== STRING REPRESENTATIONS =====
    std::string ToString() const;
    std::string BitRepresentation() const;
    std::string ToDecimalString() const;
    std::string ToHexString() const;
    std::string ToScientificString() const;
    std::string ToScientificString(int precision) const;

    // ===== CONVERSION TO INTEGER TYPES =====
    template<size_t BitSize = 64, size_t BitOffset = 0, typename IntStorageProvider = StorageProviderType>
    ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider> ToInt() const;

    template<size_t BitSize = 64, size_t BitOffset = 0, typename IntStorageProvider = StorageProviderType>
    ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider> ToUInt() const;

    // ===== ROUNDING FUNCTIONS AS MEMBER METHODS =====
    ArbitraryFloat Ceil() const;
    ArbitraryFloat Floor() const;
    ArbitraryFloat Trunc() const;
    ArbitraryFloat Round() const;
    ArbitraryFloat RoundEven() const; // banker's rounding

    // ===== MATH FUNCTIONS AS MEMBER METHODS =====
    ArbitraryFloat Abs() const;
    ArbitraryFloat Sqrt() const;
    ArbitraryFloat Cbrt() const;
    ArbitraryFloat Exp() const;
    ArbitraryFloat Exp2() const;
    ArbitraryFloat Exp10() const;
    ArbitraryFloat Expm1() const;
    ArbitraryFloat Log() const;
    ArbitraryFloat Log2() const;
    ArbitraryFloat Log10() const;
    ArbitraryFloat Log1p() const;
    ArbitraryFloat Sin() const;
    ArbitraryFloat Cos() const;
    ArbitraryFloat Tan() const;
    ArbitraryFloat Asin() const;
    ArbitraryFloat Acos() const;
    ArbitraryFloat Atan() const;
    ArbitraryFloat Sinh() const;
    ArbitraryFloat Cosh() const;
    ArbitraryFloat Tanh() const;
    ArbitraryFloat Asinh() const;
    ArbitraryFloat Acosh() const;
    ArbitraryFloat Atanh() const;

    // ===== NEXT REPRESENTABLE VALUES =====
    ArbitraryFloat NextUp() const;
    ArbitraryFloat NextDown() const;
    ArbitraryFloat NextAfter(const ArbitraryFloat& direction) const;

    // ===== SCALING OPERATIONS =====
    ArbitraryFloat Scalbn(int exp) const;
    ArbitraryFloat Ldexp(int exp) const;

    // ===== CHECKED ARITHMETIC =====
    std::optional<ArbitraryFloat> CheckedAdd(const ArbitraryFloat& other) const;
    std::optional<ArbitraryFloat> CheckedSub(const ArbitraryFloat& other) const;
    std::optional<ArbitraryFloat> CheckedMul(const ArbitraryFloat& other) const;
    std::optional<ArbitraryFloat> CheckedDiv(const ArbitraryFloat& other) const;

    // ===== FUSED OPERATIONS =====
    ArbitraryFloat Fma(const ArbitraryFloat& y, const ArbitraryFloat& z) const; // this * y + z
    ArbitraryFloat Fms(const ArbitraryFloat& y, const ArbitraryFloat& z) const; // this * y - z

    // ===== SPECIAL VALUE CONSTRUCTORS (STATIC METHODS) =====
    static ArbitraryFloat Infinity();
    static ArbitraryFloat NegativeInfinity();
    static ArbitraryFloat NaN();
    static ArbitraryFloat QuietNaN();
    static ArbitraryFloat SignalingNaN();
    static ArbitraryFloat Zero();
    static ArbitraryFloat NegativeZero();
    static ArbitraryFloat One();
    static ArbitraryFloat MinValue(); // smallest positive normal value
    static ArbitraryFloat MaxValue(); // largest finite value
    static ArbitraryFloat Epsilon(); // machine epsilon
    static ArbitraryFloat MinSubnormal(); // smallest positive subnormal value

    // ===== MATHEMATICAL CONSTANTS (STATIC METHODS) =====
    static ArbitraryFloat Pi();
    static ArbitraryFloat E();
    static ArbitraryFloat Log2E();
    static ArbitraryFloat Log10E();
    static ArbitraryFloat Ln2();
    static ArbitraryFloat Ln10();
    static ArbitraryFloat Sqrt2();
    static ArbitraryFloat Sqrt1_2(); // sqrt(1/2)
    static ArbitraryFloat Tau(); // 2*Pi
    static ArbitraryFloat InvPi(); // 1/Pi
    static ArbitraryFloat Inv2Pi(); // 1/(2*Pi)

    // ===== PRECISION AND FORMAT INFO (STATIC METHODS) =====
    static constexpr size_t ExponentBits() {
        return ExpBits;
    }
    static constexpr size_t GetMantissaBits() {
        return MantissaBits;
    }
    static constexpr size_t TotalBits() {
        return ExpBits + MantissaBits + 1;
    }
    static constexpr size_t Precision() {
        return MantissaBits + 1;
    }
    static constexpr size_t ExponentBias() {
        return (1 << (ExpBits - 1)) - 1;
    }
    static constexpr size_t MaxExponent() {
        return (1 << ExpBits) - 1;
    }
    static constexpr size_t MinExponent() {
        return 1 - ExponentBias();
    }
    static constexpr size_t MaxNormalExponent() {
        return MaxExponent() - 1 - ExponentBias();
    }

    // ===== BYTES CONVERSION =====
    std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ToBeBytes() const;
    std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ToLeBytes() const;
    std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ToNeBytes() const;
    static ArbitraryFloat FromBeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes);
    static ArbitraryFloat FromLeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes);
    static ArbitraryFloat FromNeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes);

    // ===== I/O OPERATORS =====
    friend std::ostream& operator<<(std::ostream& os, const ArbitraryFloat& af) {
        return os << af.ToString();
    }
    friend std::istream& operator>>(std::istream& is, ArbitraryFloat& af);

    // ===== STORAGE ACCESS =====
    const auto& GetStorage() const {
        return storage_;
    }
    auto& GetStorage() {
        return storage_;
    }

private:
    // Helper functions
    void Normalize();
    bool IsSpecialValue() const;
    static ArbitraryFloat FromComponents(bool sign, uint64_t exponent, uint64_t mantissa);
};

// ===== GLOBAL MATHEMATICAL FUNCTIONS =====

// Basic operations
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> Abs(const ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> Fabs(const ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& x) {
    return Abs(x);
}

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> Fmod(const ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Remainder(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, int> Remquo(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Fma(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& z);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Fmax(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Fmin(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Fdim(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

// Exponential and logarithmic functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Exp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Exp2(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Exp10(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Expm1(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Log(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Log10(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Log2(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Log1p(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

// Power functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Pow(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& base, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& exp);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Sqrt(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Cbrt(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Rsqrt(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x); // 1/sqrt(x)

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& z);

// Trigonometric functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Sin(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Cos(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Tan(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Asin(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Acos(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Atan(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Atan2(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> > Sincos(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

// Hyperbolic functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Sinh(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Cosh(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Tanh(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Asinh(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Acosh(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Atanh(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

// Error and gamma functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Erf(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Erfc(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Tgamma(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Lgamma(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

// Nearest integer floating-point operations
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Ceil(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Floor(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Trunc(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Round(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Nearbyint(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Rint(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

// Floating-point manipulation functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, int> Frexp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Ldexp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, int exp);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> > Modf(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Scalbn(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, int exp);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
int Ilogb(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Logb(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Nextafter(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& from, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& to);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Nexttoward(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& from, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& to);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Copysign(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& mag, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& sign);

// Classification functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsFinite(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsInf(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsNaN(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsNormal(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool SignBit(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsSubnormal(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsZero(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

// Comparison functions (IEEE 754 compliant)
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsLess(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsLessEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsGreater(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsGreaterEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsUnordered(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y);

// Bessel functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> J0(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> J1(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Jn(int n, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Y0(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Y1(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Yn(int n, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x);

// Additional useful functions
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Degrees(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& radians);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Radians(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& degrees);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Lerp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& a, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& b, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& t);

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Clamp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& value, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& min_val, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& max_val);

// Utility type aliases for common formats
template<typename StorageProvider>
using Float16 = ArbitraryFloat<5, 10, StorageProvider>; // IEEE 754 half precision

template<typename StorageProvider>
using BFloat16 = ArbitraryFloat<8, 7, StorageProvider>; // Google's bfloat16

template<typename StorageProvider>
using Float32 = ArbitraryFloat<8, 23, StorageProvider>; // IEEE 754 single precision

template<typename StorageProvider>
using Float64 = ArbitraryFloat<11, 52, StorageProvider>; // IEEE 754 double precision

template<typename StorageProvider>
using Float80 = ArbitraryFloat<15, 64, StorageProvider>; // x86 extended precision

template<typename StorageProvider>
using Float128 = ArbitraryFloat<15, 112, StorageProvider>; // IEEE 754 quadruple precision

template<typename StorageProvider>
using Float256 = ArbitraryFloat<19, 236, StorageProvider>; // 256-bit float

// Mixed precision operations
template<size_t E1, size_t M1, size_t E2, size_t M2, typename SP1, typename SP2>
auto Add(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename SP1, typename SP2>
auto Mul(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename SP1, typename SP2>
auto Sub(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename SP1, typename SP2>
auto Div(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1>;

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(float value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(float value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(float value) not implemented.");
}

template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(double value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(double value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(double value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(long double value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(long double value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(long double value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(T value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(T value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(T value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const std::string& str) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const std::string& str)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const std::string& str) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t BitSize, size_t BitOffset, typename IntStorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider>& value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider>& value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider>& value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t BitSize, size_t BitOffset, typename IntStorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider>& value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider>& value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider>& value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator=(T value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator=(T value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator=(T value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator float() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator float() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator float() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator double() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator double() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator long double() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator long double() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator long long() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator long long() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned long long() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned long long() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator int() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator int() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned int() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned int() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator short() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator short() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned short() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned short() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator char() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator char() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned char() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned char() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator bool() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator bool() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t NewExp, size_t NewMant, typename NewStorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator ArbitraryFloat<NewExp, NewMant, NewStorageProvider>() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator ArbitraryFloat<NewExp, NewMant, NewStorageProvider>() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator+() const {
    return *this;
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator-() const {
    return this->SetSignBit(!this.GetSignBit());
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator+(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator+(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator-(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator-(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator*(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator*(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator/(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator/(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& operator+=(const ArbitraryFloat& other) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator+=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& operator-=(const ArbitraryFloat& other) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator-=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& operator*=(const ArbitraryFloat& other) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator*=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& operator/=(const ArbitraryFloat& other) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator/=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool operator==(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator==(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool operator!=(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator!=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool operator<(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator<(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool operator<=(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator<=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool operator>(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator>(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool operator>=(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator>=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsFinite() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsFinite() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsInf() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsInf() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsNaN() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsNaN() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsNormal() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsNormal() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsSubnormal() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsSubnormal() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsZero() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsZero() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool SignBit() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::SignBit() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsPositive() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsPositive() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsNegative() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsNegative() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
int Sign() const {
    // TODO: Implement int ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Sign() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool GetSignBit() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::GetSignBit() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
void SetSignBit(bool sign) {
    // TODO: Implement void ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::SetSignBit(bool sign) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t ExpSize, size_t ExpOffset, typename ExpStorageProvider>
ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpStorageProvider> GetRawExponent() const {
    // TODO: Implement ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpStorageProvider> ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::GetRawExponent() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t ExpSize, size_t ExpOffset, typename ExpStorageProvider>
ArbitrarySignedInt<ExpSize, ExpOffset, ExpStorageProvider> GetExponent() const {
    // TODO: Implement ArbitrarySignedInt<ExpSize, ExpOffset, ExpStorageProvider> ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::GetExponent() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t MantSize, size_t MantOffset, typename MantStorageProvider>
ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProvider> GetMantissa() const {
    // TODO: Implement ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProvider> ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::GetMantissa() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t MantSize, size_t MantOffset, typename MantStorageProvider>
ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProvider> GetSignificand() const {
    // TODO: Implement ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProvider> ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::GetSignificand() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::string ToString() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ToString() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::string BitRepresentation() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::BitRepresentation() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::string ToDecimalString() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ToDecimalString() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::string ToHexString() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ToHexString() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::string ToScientificString() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ToScientificString() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::string ToScientificString(int precision) const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ToScientificString(int precision) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t BitSize, size_t BitOffset, typename IntStorageProvider>
ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider> ToInt() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider> ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ToInt() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
template<size_t BitSize, size_t BitOffset, typename IntStorageProvider>
ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider> ToUInt() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider> ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ToUInt() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Ceil() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Ceil() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Floor() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Floor() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Trunc() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Trunc() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Round() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Round() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> RoundEven() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::RoundEven() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Abs() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Abs() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Sqrt() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Sqrt() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Cbrt() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Cbrt() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Exp() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Exp() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Exp2() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Exp2() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Exp10() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Exp10() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Expm1() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Expm1() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Log() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Log() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Log2() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Log2() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Log10() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Log10() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Log1p() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Log1p() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Sin() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Sin() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Cos() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Cos() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Tan() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Tan() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Asin() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Asin() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Acos() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Acos() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Atan() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Atan() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Atan2(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Atan2(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> > Sincos(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> > Sincos(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Sinh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Sinh() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Cosh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Cosh() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Tanh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Tanh() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Asinh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Asinh() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Acosh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Acosh() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Atanh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Atanh() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Erf() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Erf() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Erfc() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Erfc() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Tgamma() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Tgamma() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Lgamma() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Lgamma() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Ceil() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Ceil() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Floor() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Floor() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Trunc() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Trunc() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Round() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Round() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> RoundEven() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::RoundEven() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Nearbyint() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Nearbyint() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Rint() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Rint() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, int> Frexp() const {
    // TODO: Implement std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, int> Frexp() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Ldexp(int exp) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Ldexp(int exp) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> > Modf() const {
    // TODO: Implement std::pair<ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>, ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> > Modf() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Scalbn(int exp) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Scalbn(int exp) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
int Ilogb() const {
    // TODO: Implement int ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Ilogb() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Logb() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Logb() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Nextafter(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& from, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& to) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Nextafter(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& from, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& to) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Nexttoward(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& from, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& to) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Nexttoward(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& from, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& to) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Copysign(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& mag, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& sign) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Copysign(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& mag, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& sign) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsFinite(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement bool IsFinite(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsInf(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement bool IsInf(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsNaN(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement bool IsNaN(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsNormal(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement bool IsNormal(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsNormal() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsSubnormal() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsSubnormal() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsZero() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::IsZero() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool SignBit() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::SignBit() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) {
    // TODO: Implement bool IsEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsLess(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) {
    // TODO: Implement bool IsLess(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsLessEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) {
    // TODO: Implement bool IsLessEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsGreater(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) {
    // TODO: Implement bool IsGreater(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsGreaterEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) {
    // TODO: Implement bool IsGreaterEqual(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
bool IsUnordered(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) {
    // TODO: Implement bool IsUnordered(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> J0(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::J0(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> J1(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::J1(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Jn(int n, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Jn(int n, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Y0(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Y0(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Y1(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Y1(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Yn(int n, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Yn(int n, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Degrees(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& radians) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Degrees(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& radians) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Radians(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& degrees) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Radians(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& degrees) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Lerp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& a, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& b, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& t) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Lerp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& a, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& b, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& t) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProvider> Clamp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& value, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& min_val, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& max_val) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::Clamp(const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& value, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& min_val, const ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>& max_val) not implemented.");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename SP1, typename SP2>
auto Add(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1> {
    // TODO: Implement auto Add(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1> not implemented.");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename SP1, typename SP2>
auto Mul(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1> {
    // TODO: Implement auto Mul(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1> not implemented.");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename SP1, typename SP2>
auto Sub(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1> {
    // TODO: Implement auto Sub(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1> not implemented.");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename SP1, typename SP2>
auto Div(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1> {
    // TODO: Implement auto Div(const ArbitraryFloat<E1, M1, SP1>& a, const ArbitraryFloat<E2, M2, SP2>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), SP1> not implemented.");
}

#endif //ARBITRARYFLOAT_H
