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

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
/**
 * Represents an arbitrary-precision floating point number with customizable
 * exponent and mantissa sizes. Provides support for IEEE 754 special values.
 * Includes a variety of operators, conversion functions, math functions,
 * rounding functions, and checked arithmetic.
 */
class ArbitraryFloat {
    static_assert(ExpBits > 1, "Exponent bits must be greater than 1.");
    static_assert(MantissaBits > 0, "Mantissa bits must be greater than 0.");

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
    explicit ArbitraryFloat(const std::string& str);

    // Constructor from arbitrary integers
    template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
    explicit ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace>& value);

    template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
    explicit ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace>& value);

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

    template<size_t NewExp, size_t NewMant, typename NewMemoryPlace>
    explicit operator ArbitraryFloat<NewExp, NewMant, NewMemoryPlace>() const;

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
    template<size_t ExpSize = ExpBits, size_t ExpOffset = 0, typename ExpMemoryPlace = MemoryPlace>
    ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpMemoryPlace> GetRawExponent() const;

    template<size_t ExpSize = ExpBits + 1, size_t ExpOffset = 0, typename ExpMemoryPlace = MemoryPlace>
    ArbitrarySignedInt<ExpSize, ExpOffset, ExpMemoryPlace> GetExponent() const;

    // Get mantissa/significand
    template<size_t MantSize, size_t MantOffset = 0, typename MantMemoryPlace = MemoryPlace>
    ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> GetMantissa() const;

    template<size_t MantSize, size_t MantOffset = 0, typename MantMemoryPlace = MemoryPlace>
    ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> GetSignificand() const;

    // ===== STRING REPRESENTATIONS =====
    std::string ToString() const;
    std::string BitRepresentation() const;
    std::string ToDecimalString() const;
    std::string ToHexString() const;
    std::string ToScientificString() const;
    std::string ToScientificString(int precision) const;

    // ===== CONVERSION TO INTEGER TYPES =====
    template<size_t BitSize = 64, size_t BitOffset = 0, typename IntMemoryPlace = MemoryPlace>
    ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace> ToInt() const;

    template<size_t BitSize = 64, size_t BitOffset = 0, typename IntMemoryPlace = MemoryPlace>
    ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace> ToUInt() const;

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
    static constexpr size_t total_bits = ExpBits + MantissaBits + 1;
    static constexpr size_t storage_bytes = (total_bits + 7) >> 3;
    using storage_type = typename MemoryPlace::template storage_type<storage_bytes>;

    static_assert(std::derived_from<storage_type, IStorage>, "MemoryPlace::storage_type must implement IStorage");

    storage_type storage_;

    // Helper functions
    void Normalize();
    bool IsSpecialValue() const;
    static ArbitraryFloat FromComponents(bool sign, uint64_t exponent, uint64_t mantissa);
};

// ===== GLOBAL MATHEMATICAL FUNCTIONS =====

// Basic operations
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Abs(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fabs(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    return Abs(x);
}

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmod(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Remainder(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, int> Remquo(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& z);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmax(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fdim(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

// Exponential and logarithmic functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp10(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Expm1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log10(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log1p(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

// Power functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Pow(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& base, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& exp);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sqrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cbrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Rsqrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x); // 1/sqrt(x)

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& z);

// Trigonometric functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tan(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Asin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Acos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atan(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atan2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > Sincos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

// Hyperbolic functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sinh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cosh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tanh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Asinh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Acosh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atanh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

// Error and gamma functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Erf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Erfc(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tgamma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Lgamma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

// Nearest integer floating-point operations
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Ceil(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Floor(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Trunc(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Round(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nearbyint(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Rint(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

// Floating-point manipulation functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, int> Frexp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Ldexp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, int exp);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > Modf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Scalbn(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, int exp);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
int Ilogb(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Logb(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nextafter(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& from, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& to);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nexttoward(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& from, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& to);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Copysign(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& mag, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& sign);

// Classification functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsFinite(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsInf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsNaN(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsNormal(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool SignBit(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsSubnormal(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsZero(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

// Comparison functions (IEEE 754 compliant)
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsLess(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsLessEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsGreater(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsGreaterEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsUnordered(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y);

// Bessel functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> J0(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> J1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Jn(int n, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Y0(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Y1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Yn(int n, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x);

// Additional useful functions
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Degrees(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& radians);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Radians(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& degrees);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Lerp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& a, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& b, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& t);

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Clamp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& value, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& min_val, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& max_val);

// Utility type aliases for common formats
template<typename MemoryPlace>
using Float16 = ArbitraryFloat<5, 10, MemoryPlace>; // IEEE 754 half precision

template<typename MemoryPlace>
using BFloat16 = ArbitraryFloat<8, 7, MemoryPlace>; // Google's bfloat16

template<typename MemoryPlace>
using Float32 = ArbitraryFloat<8, 23, MemoryPlace>; // IEEE 754 single precision

template<typename MemoryPlace>
using Float64 = ArbitraryFloat<11, 52, MemoryPlace>; // IEEE 754 double precision

template<typename MemoryPlace>
using Float80 = ArbitraryFloat<15, 64, MemoryPlace>; // x86 extended precision

template<typename MemoryPlace>
using Float128 = ArbitraryFloat<15, 112, MemoryPlace>; // IEEE 754 quadruple precision

template<typename MemoryPlace>
using Float256 = ArbitraryFloat<19, 236, MemoryPlace>; // 256-bit float

// Mixed precision operations
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Add(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Mul(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Sub(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Div(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>;

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(float value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(float value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(float value) not implemented.");
}

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(double value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(double value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(double value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(long double value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(long double value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(long double value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(T value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(T value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(T value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const std::string& str) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const std::string& str)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const std::string& str) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace>& value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace>& value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace>& value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace>& value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace>& value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace>& value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator=(T value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator=(T value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator=(T value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator float() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator float() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator float() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator double() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator double() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator double() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long double() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long double() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long double() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long long() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long long() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long long() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned long long() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned long long() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned long long() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator int() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator int() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator int() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned int() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned int() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned int() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator short() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator short() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator short() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned short() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned short() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned short() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator char() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator char() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator char() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned char() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned char() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned char() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator bool() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator bool() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator bool() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t NewExp, size_t NewMant, typename NewMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator ArbitraryFloat<NewExp, NewMant, NewMemoryPlace>() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator ArbitraryFloat<NewExp, NewMant, NewMemoryPlace>() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator ArbitraryFloat<NewExp, NewMant, NewMemoryPlace>() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+() const {
    return this;
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-() const {
    return this.SetSignBit(!this.GetSignBit());
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+(const ArbitraryFloat& other) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-(const ArbitraryFloat& other) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*(const ArbitraryFloat& other) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/(const ArbitraryFloat& other) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+=(const ArbitraryFloat& other) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+=(const ArbitraryFloat& other)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-=(const ArbitraryFloat& other) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-=(const ArbitraryFloat& other)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*=(const ArbitraryFloat& other) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*=(const ArbitraryFloat& other)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/=(const ArbitraryFloat& other) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/=(const ArbitraryFloat& other)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/=(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator==(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator==(const ArbitraryFloat& other) const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator==(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator!=(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator!=(const ArbitraryFloat& other) const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator!=(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<(const ArbitraryFloat& other) const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<=(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<=(const ArbitraryFloat& other) const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<=(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>(const ArbitraryFloat& other) const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>=(const ArbitraryFloat& other) const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>=(const ArbitraryFloat& other) const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>=(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsFinite() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsFinite() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsFinite() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsInf() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsInf() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsInf() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNaN() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNaN() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNaN() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNormal() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNormal() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNormal() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSubnormal() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSubnormal() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSubnormal() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsZero() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsZero() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsZero() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignBit() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignBit() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignBit() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsPositive() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsPositive() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsPositive() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNegative() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNegative() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNegative() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
int ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sign() const {
    // TODO: Implement int ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sign() const
    throw std::runtime_error("int ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sign() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetSignBit() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetSignBit() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetSignBit() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SetSignBit(bool sign) {
    // TODO: Implement void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SetSignBit(bool sign)
    throw std::runtime_error("void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SetSignBit(bool sign) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t ExpSize, size_t ExpOffset, typename ExpMemoryPlace>
ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetRawExponent() const {
    // TODO: Implement ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetRawExponent() const
    throw std::runtime_error("ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetRawExponent() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t ExpSize, size_t ExpOffset, typename ExpMemoryPlace>
ArbitrarySignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetExponent() const {
    // TODO: Implement ArbitrarySignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetExponent() const
    throw std::runtime_error("ArbitrarySignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetExponent() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t MantSize, size_t MantOffset, typename MantMemoryPlace>
ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetMantissa() const {
    // TODO: Implement ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetMantissa() const
    throw std::runtime_error("ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetMantissa() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t MantSize, size_t MantOffset, typename MantMemoryPlace>
ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetSignificand() const {
    // TODO: Implement ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetSignificand() const
    throw std::runtime_error("ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetSignificand() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToString() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToString() const
    throw std::runtime_error("std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToString() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::BitRepresentation() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::BitRepresentation() const
    throw std::runtime_error("std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::BitRepresentation() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToDecimalString() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToDecimalString() const
    throw std::runtime_error("std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToDecimalString() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToHexString() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToHexString() const
    throw std::runtime_error("std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToHexString() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString() const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString() const
    throw std::runtime_error("std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString(int precision) const {
    // TODO: Implement std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString(int precision) const
    throw std::runtime_error("std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString(int precision) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToInt() const {
    // TODO: Implement ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToInt() const
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToInt() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToUInt() const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToUInt() const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToUInt() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ceil() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ceil() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ceil() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Floor() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Floor() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Floor() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Trunc() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Trunc() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Trunc() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Round() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Round() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Round() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::RoundEven() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::RoundEven() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::RoundEven() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Abs() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Abs() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Abs() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cbrt() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cbrt() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cbrt() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp2() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp2() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp2() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp10() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp10() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp10() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Expm1() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Expm1() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Expm1() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log1p() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log1p() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log1p() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sin() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sin() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sin() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cos() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cos() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cos() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tan() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tan() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tan() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asin() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asin() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asin() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acos() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acos() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acos() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atan() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atan() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atan() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sinh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sinh() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sinh() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cosh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cosh() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cosh() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tanh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tanh() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tanh() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asinh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asinh() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asinh() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acosh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acosh() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acosh() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atanh() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atanh() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atanh() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextUp() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextUp() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextUp() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextDown() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextDown() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextDown() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextAfter(const ArbitraryFloat& direction) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextAfter(const ArbitraryFloat& direction) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextAfter(const ArbitraryFloat& direction) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Scalbn(int exp) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Scalbn(int exp) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Scalbn(int exp) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ldexp(int exp) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ldexp(int exp) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ldexp(int exp) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedAdd(const ArbitraryFloat& other) const {
    // TODO: Implement std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedAdd(const ArbitraryFloat& other) const
    throw std::runtime_error("std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedAdd(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedSub(const ArbitraryFloat& other) const {
    // TODO: Implement std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedSub(const ArbitraryFloat& other) const
    throw std::runtime_error("std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedSub(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedMul(const ArbitraryFloat& other) const {
    // TODO: Implement std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedMul(const ArbitraryFloat& other) const
    throw std::runtime_error("std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedMul(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedDiv(const ArbitraryFloat& other) const {
    // TODO: Implement std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedDiv(const ArbitraryFloat& other) const
    throw std::runtime_error("std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::CheckedDiv(const ArbitraryFloat& other) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fma(const ArbitraryFloat& y, const ArbitraryFloat& z) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fma(const ArbitraryFloat& y, const ArbitraryFloat& z) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fma(const ArbitraryFloat& y, const ArbitraryFloat& z) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fms(const ArbitraryFloat& y, const ArbitraryFloat& z) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fms(const ArbitraryFloat& y, const ArbitraryFloat& z) const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fms(const ArbitraryFloat& y, const ArbitraryFloat& z) const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Infinity() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Infinity()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Infinity() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NegativeInfinity() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NegativeInfinity()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NegativeInfinity() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NaN() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NaN()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NaN() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::QuietNaN() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::QuietNaN()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::QuietNaN() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignalingNaN() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignalingNaN()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignalingNaN() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Zero() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Zero()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Zero() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NegativeZero() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NegativeZero()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NegativeZero() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::One() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::One()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::One() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinValue() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinValue()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinValue() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MaxValue() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MaxValue()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MaxValue() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Epsilon() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Epsilon()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Epsilon() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinSubnormal() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinSubnormal()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinSubnormal() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Pi() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Pi()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Pi() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::E() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::E()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::E() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2E() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2E()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2E() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10E() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10E()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10E() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln2() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln2()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln2() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln10() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln10()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln10() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt2() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt2()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt2() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt1_2() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt1_2()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt1_2() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tau() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tau()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tau() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::InvPi() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::InvPi()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::InvPi() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Inv2Pi() {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Inv2Pi()
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Inv2Pi() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToBeBytes() const {
    // TODO: Implement std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToBeBytes() const
    throw std::runtime_error("std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToBeBytes() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToLeBytes() const {
    // TODO: Implement std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToLeBytes() const
    throw std::runtime_error("std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToLeBytes() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToNeBytes() const {
    // TODO: Implement std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToNeBytes() const
    throw std::runtime_error("std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToNeBytes() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromBeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromBeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromBeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromLeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromLeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromLeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromNeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromNeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromNeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Normalize() {
    // TODO: Implement void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Normalize()
    throw std::runtime_error("void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Normalize() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSpecialValue() const {
    // TODO: Implement bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSpecialValue() const
    throw std::runtime_error("bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSpecialValue() const not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromComponents(bool sign, uint64_t exponent, uint64_t mantissa) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromComponents(bool sign, uint64_t exponent, uint64_t mantissa)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromComponents(bool sign, uint64_t exponent, uint64_t mantissa) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Abs(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Abs(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Abs(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmod(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmod(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmod(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Remainder(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Remainder(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Remainder(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, int> Remquo(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, int> Remquo(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, int> Remquo(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& z) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& z)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& z) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmax(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmax(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmax(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fmin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fdim(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fdim(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Fdim(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp10(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp10(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Exp10(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Expm1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Expm1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Expm1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log10(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log10(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log10(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log1p(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log1p(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Log1p(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Pow(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& base, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& exp) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Pow(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& base, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& exp)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Pow(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& base, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& exp) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sqrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sqrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sqrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cbrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cbrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cbrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Rsqrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Rsqrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Rsqrt(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& z) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& z)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Hypot(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& z) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tan(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tan(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tan(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Asin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Asin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Asin(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Acos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Acos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Acos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atan(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atan(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atan(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atan2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atan2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atan2(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > Sincos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > Sincos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > Sincos(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sinh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sinh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Sinh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cosh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cosh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Cosh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tanh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tanh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tanh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Asinh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Asinh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Asinh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Acosh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Acosh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Acosh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atanh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atanh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Atanh(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Erf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Erf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Erf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Erfc(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Erfc(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Erfc(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tgamma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tgamma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Tgamma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Lgamma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Lgamma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Lgamma(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Ceil(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Ceil(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Ceil(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Floor(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Floor(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Floor(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Trunc(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Trunc(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Trunc(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Round(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Round(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Round(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nearbyint(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nearbyint(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nearbyint(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Rint(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Rint(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Rint(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, int> Frexp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, int> Frexp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, int> Frexp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Ldexp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, int exp) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Ldexp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, int exp)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Ldexp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, int exp) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > Modf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > Modf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("std::pair<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>, ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > Modf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Scalbn(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, int exp) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Scalbn(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, int exp)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Scalbn(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, int exp) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
int Ilogb(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement int Ilogb(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("int Ilogb(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Logb(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Logb(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Logb(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nextafter(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& from, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& to) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nextafter(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& from, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& to)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nextafter(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& from, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& to) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nexttoward(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& from, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& to) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nexttoward(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& from, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& to)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Nexttoward(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& from, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& to) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Copysign(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& mag, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& sign) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Copysign(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& mag, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& sign)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Copysign(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& mag, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& sign) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsFinite(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement bool IsFinite(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("bool IsFinite(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsInf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement bool IsInf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("bool IsInf(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsNaN(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement bool IsNaN(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("bool IsNaN(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsNormal(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement bool IsNormal(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("bool IsNormal(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool SignBit(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement bool SignBit(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("bool SignBit(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsSubnormal(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement bool IsSubnormal(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("bool IsSubnormal(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsZero(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement bool IsZero(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("bool IsZero(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement bool IsEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("bool IsEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsLess(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement bool IsLess(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("bool IsLess(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsLessEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement bool IsLessEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("bool IsLessEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsGreater(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement bool IsGreater(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("bool IsGreater(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsGreaterEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement bool IsGreaterEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("bool IsGreaterEqual(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool IsUnordered(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) {
    // TODO: Implement bool IsUnordered(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y)
    throw std::runtime_error("bool IsUnordered(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& y) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> J0(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> J0(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> J0(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> J1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> J1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> J1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Jn(int n, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Jn(int n, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Jn(int n, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Y0(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Y0(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Y0(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Y1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Y1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Y1(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Yn(int n, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Yn(int n, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Yn(int n, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& x) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Degrees(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& radians) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Degrees(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& radians)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Degrees(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& radians) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Radians(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& degrees) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Radians(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& degrees)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Radians(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& degrees) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Lerp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& a, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& b, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& t) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Lerp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& a, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& b, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& t)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Lerp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& a, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& b, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& t) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Clamp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& value, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& min_val, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& max_val) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Clamp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& value, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& min_val, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& max_val)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> Clamp(const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& value, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& min_val, const ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& max_val) not implemented.");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Add(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
    // TODO: Implement auto Add(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>
    throw std::runtime_error("auto Add(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> not implemented.");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Mul(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
    // TODO: Implement auto Mul(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>
    throw std::runtime_error("auto Mul(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> not implemented.");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Sub(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
    // TODO: Implement auto Sub(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>
    throw std::runtime_error("auto Sub(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> not implemented.");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Div(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
    // TODO: Implement auto Div(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>
    throw std::runtime_error("auto Div(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> not implemented.");
}

#endif //ARBITRARYFLOAT_H
