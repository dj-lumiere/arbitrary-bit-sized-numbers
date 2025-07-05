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

#include <concepts/StorageProvider.h>

template<size_t BitSize, size_t BitOffset, typename StorageProviderType>
class ArbitrarySignedInt;

template<size_t BitSize, size_t BitOffset, typename StorageProviderType>
class ArbitraryUnsignedInt;

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
    template<size_t BitSize, size_t BitOffset, typename IntStorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
    explicit ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntStorageProviderType>& value);

    template<size_t BitSize, size_t BitOffset, typename IntStorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
    explicit ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProviderType>& value);

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

    template<size_t NewExp, size_t NewMant, typename NewStorageProviderType> requires StorageProvider<NewStorageProviderType, ((NewExp + NewMant + 1 + 7) >> 3)>
    explicit operator ArbitraryFloat<NewExp, NewMant, NewStorageProviderType>() const;

    // ===== UNARY OPERATORS =====
    ArbitraryFloat operator+() const; // unary plus
    ArbitraryFloat operator-() const; // unary minus

    // ===== ARITHMETIC OPERATORS =====
    ArbitraryFloat operator+(const ArbitraryFloat& other) const;
    ArbitraryFloat operator-(const ArbitraryFloat& other) const;
    ArbitraryFloat operator*(const ArbitraryFloat& other) const;
    ArbitraryFloat operator/(const ArbitraryFloat& other) const;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    auto operator+(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const -> ArbitraryFloat<std::max(ExpBits, OtherExpBits), std::max(MantissaBits, OtherMantBits), StorageProviderType>;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    auto operator-(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const -> ArbitraryFloat<std::max(ExpBits, OtherExpBits), std::max(MantissaBits, OtherMantBits), StorageProviderType>;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    auto operator*(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const -> ArbitraryFloat<std::max(ExpBits, OtherExpBits), std::max(MantissaBits, OtherMantBits), StorageProviderType>;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    auto operator/(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const -> ArbitraryFloat<std::max(ExpBits, OtherExpBits), std::max(MantissaBits, OtherMantBits), StorageProviderType>;

    // ===== ASSIGNMENT ARITHMETIC OPERATORS =====
    ArbitraryFloat& operator+=(const ArbitraryFloat& other);
    ArbitraryFloat& operator-=(const ArbitraryFloat& other);
    ArbitraryFloat& operator*=(const ArbitraryFloat& other);
    ArbitraryFloat& operator/=(const ArbitraryFloat& other);
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    ArbitraryFloat& operator+=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other);
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    ArbitraryFloat& operator-=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other);
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    ArbitraryFloat& operator*=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other);
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    ArbitraryFloat& operator/=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other);
    
    // ===== COMPARISON OPERATORS =====
    bool operator==(const ArbitraryFloat& other) const;
    bool operator!=(const ArbitraryFloat& other) const;
    bool operator<(const ArbitraryFloat& other) const;
    bool operator<=(const ArbitraryFloat& other) const;
    bool operator>(const ArbitraryFloat& other) const;
    bool operator>=(const ArbitraryFloat& other) const;
    std::partial_ordering operator<=>(const ArbitraryFloat& other) const;

    // ===== MIXED PRECISION COMPARION OPERATORS =====
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    bool operator==(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    bool operator!=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    bool operator<(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    bool operator<=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    bool operator>(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    bool operator>=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const;
    template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
    std::partial_ordering operator<=>(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const;

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
    template<size_t ExpSize = ExpBits, size_t ExpOffset = 0, typename ExpStorageProviderType = StorageProviderType>
    ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpStorageProviderType> GetRawExponent() const;

    template<size_t ExpSize = ExpBits, size_t ExpOffset = 0, typename ExpStorageProviderType = StorageProviderType>
    ArbitrarySignedInt<ExpSize, ExpOffset, ExpStorageProviderType> GetExponent() const;

    // Get mantissa/significand
    template<size_t MantSize, size_t MantOffset = 0, typename MantStorageProviderType = StorageProviderType>
    ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProviderType> GetMantissa() const;

    template<size_t MantSize, size_t MantOffset = 0, typename MantStorageProviderType = StorageProviderType>
    ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProviderType> GetSignificand() const;

    // ===== STRING REPRESENTATIONS =====
    std::string ToString() const;
    std::string BitRepresentation() const;
    std::string ToDecimalString() const;
    std::string ToHexString() const;
    std::string ToScientificString() const;
    std::string ToScientificString(int precision) const;

    // ===== CONVERSION TO INTEGER TYPES =====
    template<size_t BitSize, size_t BitOffset = 0, typename IntStorageProviderType = StorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
    ArbitrarySignedInt<BitSize, BitOffset, IntStorageProviderType> ToInt() const;

    template<size_t BitSize, size_t BitOffset = 0, typename UIntStorageProviderType = StorageProviderType> requires StorageProvider<UIntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
    ArbitraryUnsignedInt<BitSize, BitOffset, UIntStorageProviderType> ToUInt() const;

    // ===== ROUNDING FUNCTIONS AS MEMBER METHODS =====
    ArbitraryFloat Ceil() const;
    ArbitraryFloat Floor() const;
    ArbitraryFloat Trunc() const;
    ArbitraryFloat Round() const;
    ArbitraryFloat RoundEven() const; // banker's rounding

    // ===== BASIC MATH FUNCTIONS =====
    ArbitraryFloat Abs() const;
    ArbitraryFloat Fmod(const ArbitraryFloat& other) const;
    ArbitraryFloat Remainder(const ArbitraryFloat& other) const;

    // ===== POWER FUNCTIONS =====
    ArbitraryFloat Pow(const ArbitraryFloat& exponent) const;
    ArbitraryFloat Hypot(const ArbitraryFloat& other) const;
    ArbitraryFloat Hypot(const ArbitraryFloat& y, const ArbitraryFloat& z) const;
    ArbitraryFloat Sqrt() const;
    ArbitraryFloat RSqrt() const;
    ArbitraryFloat Cbrt() const;

    // ===== EXPONENTIAL & LOGARITHMIC FUNCTIONS =====
    ArbitraryFloat Exp() const;
    ArbitraryFloat Exp2() const;
    ArbitraryFloat Exp10() const;
    ArbitraryFloat Expm1() const;
    ArbitraryFloat Log() const;
    ArbitraryFloat Log2() const;
    ArbitraryFloat Log10() const;
    ArbitraryFloat Log1p() const;
    ArbitraryFloat Logb(const ArbitraryFloat& y) const;

    // ===== TRIGONOMETRIC FUNCTIONS =====
    ArbitraryFloat Sin() const;
    ArbitraryFloat Cos() const;
    ArbitraryFloat Tan() const;
    ArbitraryFloat Asin() const;
    ArbitraryFloat Acos() const;
    ArbitraryFloat Atan() const;
    ArbitraryFloat Atan2(const ArbitraryFloat& x) const;

    // ===== HYPERBOLIC FUNCTIONS =====
    ArbitraryFloat Sinh() const;
    ArbitraryFloat Cosh() const;
    ArbitraryFloat Tanh() const;
    ArbitraryFloat Asinh() const;
    ArbitraryFloat Acosh() const;
    ArbitraryFloat Atanh() const;

    // ===== FUSED OPERATIONS =====
    ArbitraryFloat Fma(const ArbitraryFloat& y, const ArbitraryFloat& z) const;
    ArbitraryFloat Fms(const ArbitraryFloat& y, const ArbitraryFloat& z) const;

    // ===== SPECIAL FUNCTIONS =====
    ArbitraryFloat Erf() const;
    ArbitraryFloat Erfc() const;
    ArbitraryFloat Lgamma() const;
    ArbitraryFloat Tgamma() const;
    ArbitraryFloat J0() const;
    ArbitraryFloat J1() const;
    ArbitraryFloat Jn(int n) const;
    ArbitraryFloat Y0() const;
    ArbitraryFloat Y1() const;
    ArbitraryFloat Yn(int n) const;
    ArbitraryFloat Ldexp(int exp) const;
    ArbitraryFloat ToRadians() const;
    ArbitraryFloat RadiansToDegrees() const;
    ArbitraryFloat Lerp(const ArbitraryFloat& other, const ArbitraryFloat& t) const;
    ArbitraryFloat Clamp(const ArbitraryFloat& min, const ArbitraryFloat& max) const;
    template<typename T> requires std::is_integral_v<T>
    ArbitraryFloat Scalbn(T exp) const;
    template<size_t BitSize, size_t BitOffset, typename IntStorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
    ArbitraryFloat Scalbn(ArbitrarySignedInt<BitSize, BitOffset, IntStorageProviderType> exp) const;
    template<size_t BitSize, size_t BitOffset, typename IntStorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
    ArbitraryFloat Scalbn(ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProviderType> exp) const;
    template<typename T> requires std::is_integral_v<T>
    ArbitraryFloat Ldexp(T exp) const;
    template<size_t BitSize, size_t BitOffset, typename IntStorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
    ArbitraryFloat Ldexp(ArbitrarySignedInt<BitSize, BitOffset, IntStorageProviderType> exp) const;
    template<size_t BitSize, size_t BitOffset, typename IntStorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
    ArbitraryFloat Ldexp(ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProviderType> exp) const;

    // ===== NEXT REPRESENTABLE VALUES =====
    ArbitraryFloat NextUp() const;
    ArbitraryFloat NextDown() const;
    ArbitraryFloat NextAfter(const ArbitraryFloat& direction) const;

    // ===== CHECKED ARITHMETIC =====
    std::optional<ArbitraryFloat> CheckedAdd(const ArbitraryFloat& other) const;
    std::optional<ArbitraryFloat> CheckedSub(const ArbitraryFloat& other) const;
    std::optional<ArbitraryFloat> CheckedMul(const ArbitraryFloat& other) const;
    std::optional<ArbitraryFloat> CheckedDiv(const ArbitraryFloat& other) const;

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
    friend std::istream& operator>>(std::istream& is, ArbitraryFloat& af) {
        std::string s;
        is >> s;
        af = ArbitraryFloat(s);
        return is;
    }

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

#include <core/float/impl/ArbitraryFloatImpl.h>
#include <core/float/utility_ops/ArbitraryFloatUtilityOps.h>

// Utility type aliases for common formats
template<typename StorageProviderType>
using Float16 = ArbitraryFloat<5, 10, StorageProviderType>; // IEEE 754 half precision

template<typename StorageProviderType>
using BFloat16 = ArbitraryFloat<8, 7, StorageProviderType>; // Google's bfloat16

template<typename StorageProviderType>
using Float32 = ArbitraryFloat<8, 23, StorageProviderType>; // IEEE 754 single precision

template<typename StorageProviderType>
using Float64 = ArbitraryFloat<11, 52, StorageProviderType>; // IEEE 754 double precision

template<typename StorageProviderType>
using Float80 = ArbitraryFloat<15, 64, StorageProviderType>; // x86 extended precision

template<typename StorageProviderType>
using Float128 = ArbitraryFloat<15, 112, StorageProviderType>; // IEEE 754 quadruple precision

template<typename StorageProviderType>
using Float256 = ArbitraryFloat<19, 236, StorageProviderType>; // 256-bit float

#endif //ARBITRARYFLOAT_H
