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
    /**
     * 
     * @return 
     */
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
    
    static_assert(std::derived_from<storage_type, IStorage>,
        "MemoryPlace::storage_type must implement IStorage");
    
    storage_type storage_;

    // Helper functions
    void Normalize();
    bool IsSpecialValue() const;
    static ArbitraryFloat FromComponents(bool sign, uint64_t exponent, uint64_t mantissa);
};

// ===== GLOBAL MATHEMATICAL FUNCTIONS =====

// Basic operations
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Abs(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fabs(const ArbitraryFloat<E, M, MP>& x) {
    return Abs(x);
}

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmod(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Remainder(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, int> Remquo(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fma(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y,
    const ArbitraryFloat<E, M, MP>& z);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmax(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmin(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fdim(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

// Exponential and logarithmic functions
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp2(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp10(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Expm1(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log10(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log2(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log1p(const ArbitraryFloat<E, M, MP>& x);

// Power functions
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Pow(const ArbitraryFloat<E, M, MP>& base, const ArbitraryFloat<E, M, MP>& exp);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sqrt(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cbrt(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Rsqrt(const ArbitraryFloat<E, M, MP>& x); // 1/sqrt(x)

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Hypot(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Hypot(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y,
    const ArbitraryFloat<E, M, MP>& z);

// Trigonometric functions
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sin(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cos(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tan(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Asin(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Acos(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atan(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atan2(const ArbitraryFloat<E, M, MP>& y, const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, ArbitraryFloat<E, M, MP> > Sincos(const ArbitraryFloat<E, M, MP>& x);

// Hyperbolic functions
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sinh(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cosh(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tanh(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Asinh(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Acosh(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atanh(const ArbitraryFloat<E, M, MP>& x);

// Error and gamma functions
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Erf(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Erfc(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tgamma(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Lgamma(const ArbitraryFloat<E, M, MP>& x);

// Nearest integer floating-point operations
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Ceil(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Floor(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Trunc(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Round(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nearbyint(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Rint(const ArbitraryFloat<E, M, MP>& x);

// Floating-point manipulation functions
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, int> Frexp(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Ldexp(const ArbitraryFloat<E, M, MP>& x, int exp);

template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, ArbitraryFloat<E, M, MP> > Modf(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Scalbn(const ArbitraryFloat<E, M, MP>& x, int exp);

template<size_t E, size_t M, typename MP>
int Ilogb(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Logb(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nextafter(const ArbitraryFloat<E, M, MP>& from, const ArbitraryFloat<E, M, MP>& to);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nexttoward(const ArbitraryFloat<E, M, MP>& from, const ArbitraryFloat<E, M, MP>& to);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Copysign(const ArbitraryFloat<E, M, MP>& mag, const ArbitraryFloat<E, M, MP>& sign);

// Classification functions
template<size_t E, size_t M, typename MP>
bool IsFinite(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
bool IsInf(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
bool IsNaN(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
bool IsNormal(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
bool SignBit(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
bool IsSubnormal(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
bool IsZero(const ArbitraryFloat<E, M, MP>& x);

// Comparison functions (IEEE 754 compliant)
template<size_t E, size_t M, typename MP>
bool IsEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
bool IsLess(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
bool IsLessEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
bool IsGreater(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
bool IsGreaterEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

template<size_t E, size_t M, typename MP>
bool IsUnordered(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y);

// Bessel functions
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> J0(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> J1(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Jn(int n, const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Y0(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Y1(const ArbitraryFloat<E, M, MP>& x);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Yn(int n, const ArbitraryFloat<E, M, MP>& x);

// Additional useful functions
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Degrees(const ArbitraryFloat<E, M, MP>& radians);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Radians(const ArbitraryFloat<E, M, MP>& degrees);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Lerp(const ArbitraryFloat<E, M, MP>& a,
    const ArbitraryFloat<E, M, MP>& b,
    const ArbitraryFloat<E, M, MP>& t);

template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Clamp(const ArbitraryFloat<E, M, MP>& value,
    const ArbitraryFloat<E, M, MP>& min_val,
    const ArbitraryFloat<E, M, MP>& max_val);

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
auto Add(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b)
    -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Mul(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b)
    -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Sub(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b)
    -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>;

template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Div(const ArbitraryFloat<E1, M1, MP>& a, const ArbitraryFloat<E2, M2, MP>& b)
    -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP>;

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(float value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}

template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(double value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(long double value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(T value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(const std::string& str) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(
    const ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace>& value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ArbitraryFloat(
    const ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace>& value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator
=(T value) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator float() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator double() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long double() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator long long() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned long long() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator int() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned int() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator short() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned short() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator char() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator unsigned char() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator bool() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t NewExp, size_t NewMant, typename NewMemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator ArbitraryFloat<NewExp, NewMant, NewMemoryPlace>() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
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
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-(
    const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*(
    const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/(
    const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator+=(
    const ArbitraryFloat& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator-=(
    const ArbitraryFloat& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator*=(
    const ArbitraryFloat& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>& ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator/=(
    const ArbitraryFloat& other) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator==(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator!=(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator<=(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::operator>=(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsFinite() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsInf() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNaN() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNormal() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSubnormal() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsZero() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignBit() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsPositive() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsNegative() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
int ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sign() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::GetSignBit() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SetSignBit(bool sign) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t ExpSize, size_t ExpOffset, typename ExpMemoryPlace>
ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
GetRawExponent() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t ExpSize, size_t ExpOffset, typename ExpMemoryPlace>
ArbitrarySignedInt<ExpSize, ExpOffset, ExpMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
GetExponent() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t MantSize, size_t MantOffset, typename MantMemoryPlace>
ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
GetMantissa() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t MantSize, size_t MantOffset, typename MantMemoryPlace>
ArbitraryUnsignedInt<MantSize, MantOffset, MantMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
GetSignificand() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToString() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::BitRepresentation() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToDecimalString() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToHexString() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::string ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToScientificString(int precision) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitrarySignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
ToInt() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
template<size_t BitSize, size_t BitOffset, typename IntMemoryPlace>
ArbitraryUnsignedInt<BitSize, BitOffset, IntMemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
ToUInt() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ceil() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Floor() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Trunc() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Round() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
RoundEven() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Abs() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cbrt() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp2() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Exp10() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Expm1() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log1p() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sin() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cos() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tan() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asin() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acos() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atan() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sinh() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Cosh() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tanh() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Asinh() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Acosh() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Atanh() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextUp() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
NextDown() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NextAfter(
    const ArbitraryFloat& direction) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
Scalbn(int exp) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
Ldexp(int exp) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
CheckedAdd(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
CheckedSub(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
CheckedMul(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> > ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
CheckedDiv(const ArbitraryFloat& other) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fma(
    const ArbitraryFloat& y, const ArbitraryFloat& z) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Fms(
    const ArbitraryFloat& y, const ArbitraryFloat& z) const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Infinity() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::
NegativeInfinity() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NaN() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::QuietNaN() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::SignalingNaN() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Zero() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::NegativeZero() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::One() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinValue() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MaxValue() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Epsilon() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::MinSubnormal() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Pi() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::E() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log2E() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Log10E() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln2() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Ln10() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt2() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Sqrt1_2() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Tau() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::InvPi() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Inv2Pi() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToBeBytes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToLeBytes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::ToNeBytes() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromBeBytes(
    const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromLeBytes(
    const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromNeBytes(
    const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
void ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::Normalize() {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
bool ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::IsSpecialValue() const {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t ExpBits, size_t MantissaBits, typename MemoryPlace>
ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace> ArbitraryFloat<ExpBits, MantissaBits, MemoryPlace>::FromComponents(
    bool sign, uint64_t exponent, uint64_t mantissa) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Abs(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmod(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Remainder(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, int> Remquo(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fma(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y,
    const ArbitraryFloat<E, M, MP>& z) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmax(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fmin(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Fdim(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp2(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Exp10(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Expm1(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log10(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log2(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Log1p(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Pow(const ArbitraryFloat<E, M, MP>& base, const ArbitraryFloat<E, M, MP>& exp) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sqrt(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cbrt(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Rsqrt(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Hypot(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Hypot(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y,
    const ArbitraryFloat<E, M, MP>& z) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sin(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cos(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tan(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Asin(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Acos(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atan(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atan2(const ArbitraryFloat<E, M, MP>& y, const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, ArbitraryFloat<E, M, MP> > Sincos(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Sinh(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Cosh(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tanh(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Asinh(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Acosh(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Atanh(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Erf(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Erfc(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Tgamma(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Lgamma(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Ceil(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Floor(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Trunc(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Round(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nearbyint(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Rint(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, int> Frexp(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Ldexp(const ArbitraryFloat<E, M, MP>& x, int exp) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
std::pair<ArbitraryFloat<E, M, MP>, ArbitraryFloat<E, M, MP> > Modf(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Scalbn(const ArbitraryFloat<E, M, MP>& x, int exp) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
int Ilogb(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Logb(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nextafter(const ArbitraryFloat<E, M, MP>& from, const ArbitraryFloat<E, M, MP>& to) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Nexttoward(const ArbitraryFloat<E, M, MP>& from, const ArbitraryFloat<E, M, MP>& to) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Copysign(const ArbitraryFloat<E, M, MP>& mag, const ArbitraryFloat<E, M, MP>& sign) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsFinite(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsInf(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsNaN(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsNormal(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool SignBit(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsSubnormal(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsZero(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsLess(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsLessEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsGreater(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsGreaterEqual(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
bool IsUnordered(const ArbitraryFloat<E, M, MP>& x, const ArbitraryFloat<E, M, MP>& y) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> J0(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> J1(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Jn(int n, const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Y0(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Y1(const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Yn(int n, const ArbitraryFloat<E, M, MP>& x) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Degrees(const ArbitraryFloat<E, M, MP>& radians) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Radians(const ArbitraryFloat<E, M, MP>& degrees) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Lerp(const ArbitraryFloat<E, M, MP>& a, const ArbitraryFloat<E, M, MP>& b,
    const ArbitraryFloat<E, M, MP>& t) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E, size_t M, typename MP>
ArbitraryFloat<E, M, MP> Clamp(const ArbitraryFloat<E, M, MP>& value, const ArbitraryFloat<E, M, MP>& min_val,
    const ArbitraryFloat<E, M, MP>& max_val) {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Add(const ArbitraryFloat<E1, M1, MP>& a,
    const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Mul(const ArbitraryFloat<E1, M1, MP>& a,
    const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Sub(const ArbitraryFloat<E1, M1, MP>& a,
    const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}
template<size_t E1, size_t M1, size_t E2, size_t M2, typename MP>
auto Div(const ArbitraryFloat<E1, M1, MP>& a,
    const ArbitraryFloat<E2, M2, MP>& b) -> ArbitraryFloat<std::max(E1, E2), std::max(M1, M2), MP> {
    // TODO: Implement this
    throw std::runtime_error("Not implemented");
}

#endif //ARBITRARYFLOAT_H