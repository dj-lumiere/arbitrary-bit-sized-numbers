//
// Created by Lumi on 25. 6. 18.
//
#include <gtest/gtest.h>
#include "../include/core/unsigned-int/ArbitraryUnsignedInt.h"
#include "../include/storage/cpu-storage/CPUStorage.h"
#include <array>

class ArbitraryUnsignedIntTest : public ::testing::Test {
protected:
    using UInt8 = ArbitraryUnsignedInt<8, 0, CPUStorageProvider>;
    using UInt16 = ArbitraryUnsignedInt<16, 0, CPUStorageProvider>;
    using UInt32 = ArbitraryUnsignedInt<32, 0, CPUStorageProvider>;
    using UInt64 = ArbitraryUnsignedInt<64, 0, CPUStorageProvider>;
    using UInt128 = ArbitraryUnsignedInt<128, 0, CPUStorageProvider>;
    using UInt256 = ArbitraryUnsignedInt<256, 0, CPUStorageProvider>;
};

TEST(ArbitraryUnsignedIntTest, Constructors) {
    ArbitraryUnsignedInt<8, 0, CPUStorageProvider> a;
    ASSERT_EQ(a.GetStorage()[0], 0);

    ArbitraryUnsignedInt<16, 0, CPUStorageProvider> b(128);
    ASSERT_EQ(b.GetStorage()[0], 128);
    ASSERT_EQ(b.GetStorage()[1], 0);

    ArbitraryUnsignedInt<32, 0, CPUStorageProvider> c(0x12345678);
    std::array<uint8_t, 4> expected_c = { 0x78, 0x56, 0x34, 0x12 };
    ASSERT_EQ(c.GetStorage().data_, expected_c);

    ArbitraryUnsignedInt<64, 0, CPUStorageProvider> d("12345678901234567890"); // 0xAB54A98CEB1F0AD2
    std::array<uint8_t, 8> expected_d = { 0xD2, 0x0A, 0x1F, 0xEB, 0x8C, 0xA9, 0x54, 0xAB };
    ASSERT_EQ(d.GetStorage().data_, expected_d);

    ArbitraryUnsignedInt<128, 0, CPUStorageProvider> e(std::string("340282366920938463463374607431768211455")); // 2^128 - 1
    std::array<uint8_t, 16> expected_e = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    ASSERT_EQ(e.GetStorage().data_, expected_e);

    ArbitraryUnsignedInt<256, 0, CPUStorageProvider> f(std::string("115792089237316195423570985008687907853269984665640564039457584007913129639935")); // 2^256 - 1
    std::array<uint8_t, 32> expected_f = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    ASSERT_EQ(f.GetStorage().data_, expected_f);

    ArbitraryUnsignedInt<256, 0, CPUStorageProvider> g("1234567890987654321234567890987654321012345678909876543210123456");
    std::array<uint8_t, 32> expected_g = { 192, 240, 247, 127, 251, 101, 216, 44, 90, 207, 20, 123, 34, 137, 10, 156, 141, 131, 48, 85, 192, 44, 24, 3, 70, 0, 3, 0, 0, 0, 0, 0 };
    ASSERT_EQ(g.GetStorage().data_, expected_g);
}

TEST(ArbitraryUnsignedIntTest, Arithmetics) {
    using UInt8 = ArbitraryUnsignedInt<8, 0, CPUStorageProvider>;
    using UInt16 = ArbitraryUnsignedInt<16, 0, CPUStorageProvider>;
    using UInt32 = ArbitraryUnsignedInt<32, 0, CPUStorageProvider>;

    // Addition
    UInt8 a(10), b(20);
    ASSERT_EQ((a + b).GetStorage()[0], 30);

    UInt8 c(250), d(10);
    ASSERT_EQ((c + d).GetStorage()[0], 4); // 250 + 10 = 260, wraps to 4 (260 % 256)

    UInt32 a2(0xFFFFFF), b2(0xFFFFFF);
    std::array<uint8_t, 4> expected_a2 = { 254, 255, 255, 1 };
    ASSERT_EQ((a2 + b2).GetStorage().data_, expected_a2);

    // Subtraction
    UInt8 e(30), f(10);
    ASSERT_EQ((e - f).GetStorage()[0], 20);

    UInt8 g(5), h(10);
    ASSERT_EQ((g - h).GetStorage()[0], 251); // 5 - 10 = -5, wraps to 251 (256 - 5)
    
    UInt32 e2(0x1), f2(0xFFFFFF);
    std::array<uint8_t, 4> expected_e2 = { 2, 0, 0, 255 };
    ASSERT_EQ((e2 - f2).GetStorage().data_, expected_e2);

    // Multiplication
    UInt8 i(5), j(6);
    ASSERT_EQ((i * j).GetStorage()[0], 30);

    UInt8 k(20), l(20);
    ASSERT_EQ((k * l).GetStorage()[0], 144); // 20 * 20 = 400, wraps to 144 (400 % 256)

    // Division
    UInt8 m(100), n(10);
    ASSERT_EQ((m / n).GetStorage()[0], 10);

    UInt8 o(10), p(3);
    ASSERT_EQ((o / p).GetStorage()[0], 3);

    // Modulo
    UInt8 q(10), r(3);
    ASSERT_EQ((q % r).GetStorage()[0], 1);

    UInt8 s(100), t(10);
    ASSERT_EQ((s % t).GetStorage()[0], 0);

    // DivRem
    UInt8 u(100), v(10);
    auto divrem_result1 = u.DivRem(v);
    ASSERT_EQ(divrem_result1.first.GetStorage()[0], 10);
    ASSERT_EQ(divrem_result1.second.GetStorage()[0], 0);

    UInt8 w(10), x(3);
    auto divrem_result2 = w.DivRem(x);
    ASSERT_EQ(divrem_result2.first.GetStorage()[0], 3);
    ASSERT_EQ(divrem_result2.second.GetStorage()[0], 1);

    // Division by zero
    UInt8 zero(0);
    ASSERT_THROW(m / zero, std::runtime_error);
    ASSERT_THROW(q % zero, std::runtime_error);
    ASSERT_THROW(u.DivRem(zero), std::runtime_error);
}

TEST(ArbitraryUnsignedIntTest, OverflowingArithmetics) {
    using UInt8 = ArbitraryUnsignedInt<8, 0, CPUStorageProvider>;

    // OverflowingMul
    UInt8 a(10), b(5);
    auto overflowing_mul_result1 = a.OverflowingMul(b);
    ASSERT_EQ(overflowing_mul_result1.first.GetStorage()[0], 50);
    ASSERT_FALSE(overflowing_mul_result1.second);

    UInt8 c(20), d(20); // 20 * 20 = 400, overflows UInt8
    auto overflowing_mul_result2 = c.OverflowingMul(d);
    ASSERT_EQ(overflowing_mul_result2.first.GetStorage()[0], 144); // 400 % 256
    ASSERT_TRUE(overflowing_mul_result2.second);

    // OverflowingDiv
    UInt8 e(100), f(10);
    auto overflowing_div_result1 = e.OverflowingDiv(f);
    ASSERT_EQ(overflowing_div_result1.first.GetStorage()[0], 10);
    ASSERT_FALSE(overflowing_div_result1.second);

    // OverflowingRem
    UInt8 g(10), h(3);
    auto overflowing_rem_result1 = g.OverflowingRem(h);
    ASSERT_EQ(overflowing_rem_result1.first.GetStorage()[0], 1);
    ASSERT_FALSE(overflowing_rem_result1.second);

    // OverflowingPow
    UInt8 i(2), j(3); // 2^3 = 8
    auto overflowing_pow_result1 = i.OverflowingPow(j);
    ASSERT_EQ(overflowing_pow_result1.first.GetStorage()[0], 8);
    ASSERT_FALSE(overflowing_pow_result1.second);

    UInt8 k(2), l(8); // 2^8 = 256, overflows UInt8
    auto overflowing_pow_result2 = k.OverflowingPow(l);
    ASSERT_EQ(overflowing_pow_result2.first.GetStorage()[0], 0); // 256 % 256
    ASSERT_TRUE(overflowing_pow_result2.second);

    // OverflowingShl
    UInt8 m(10); // 00001010
    auto overflowing_shl_result1 = m.OverflowingShl(1);
    ASSERT_EQ(overflowing_shl_result1.first.GetStorage()[0], 20); // 00010100
    ASSERT_FALSE(overflowing_shl_result1.second);

    UInt8 n(128); // 10000000
    auto overflowing_shl_result2 = n.OverflowingShl(1);
    ASSERT_EQ(overflowing_shl_result2.first.GetStorage()[0], 0); // 00000000 (overflow)
    ASSERT_TRUE(overflowing_shl_result2.second);

    // OverflowingShr
    UInt8 o(20); // 00010100
    auto overflowing_shr_result1 = o.OverflowingShr(1);
    ASSERT_EQ(overflowing_shr_result1.first.GetStorage()[0], 10); // 00001010
    ASSERT_FALSE(overflowing_shr_result1.second);
}
TEST(ArbitraryUnsignedIntTest, SaturatingArithmetics) {
    using UInt8 = ArbitraryUnsignedInt<8, 0, CPUStorageProvider>;

    // SaturatingMul
    UInt8 a(10), b(5);
    ASSERT_EQ(a.SaturatingMul(b).GetStorage()[0], 50);

    UInt8 c(20), d(20); // 20 * 20 = 400, overflows UInt8
    ASSERT_EQ(c.SaturatingMul(d).GetStorage()[0], 255); // Should saturate to max

    // SaturatingPow
    UInt8 e(2), f(3); // 2^3 = 8
    ASSERT_EQ(e.SaturatingPow(f).GetStorage()[0], 8);

    UInt8 g(2), h(8); // 2^8 = 256, overflows UInt8
    ASSERT_EQ(g.SaturatingPow(h).GetStorage()[0], 255); // Should saturate to max
}
TEST(ArbitraryUnsignedIntTest, CheckedArithmetics) {
    using UInt8 = ArbitraryUnsignedInt<8, 0, CPUStorageProvider>;

    // CheckedMul
    UInt8 a(10), b(5);
    auto checked_mul_result1 = a.CheckedMul(b);
    ASSERT_TRUE(checked_mul_result1.has_value());
    ASSERT_EQ(checked_mul_result1.value().GetStorage()[0], 50);

    UInt8 c(20), d(20); // 20 * 20 = 400, overflows UInt8
    auto checked_mul_result2 = c.CheckedMul(d);
    ASSERT_FALSE(checked_mul_result2.has_value());

    // CheckedDiv
    UInt8 e(100), f(10);
    auto checked_div_result1 = e.CheckedDiv(f);
    ASSERT_TRUE(checked_div_result1.has_value());
    ASSERT_EQ(checked_div_result1.value().GetStorage()[0], 10);

    UInt8 g(10), zero(0);
    auto checked_div_result2 = g.CheckedDiv(zero);
    ASSERT_FALSE(checked_div_result2.has_value());

    // CheckedRem
    UInt8 h(10), i(3);
    auto checked_rem_result1 = h.CheckedRem(i);
    ASSERT_TRUE(checked_rem_result1.has_value());
    ASSERT_EQ(checked_rem_result1.value().GetStorage()[0], 1);

    UInt8 j(10), zero2(0);
    auto checked_rem_result2 = j.CheckedRem(zero2);
    ASSERT_FALSE(checked_rem_result2.has_value());

    // CheckedPow
    UInt8 k(2), l(3); // 2^3 = 8
    auto checked_pow_result1 = k.CheckedPow(l);
    ASSERT_TRUE(checked_pow_result1.has_value());
    ASSERT_EQ(checked_pow_result1.value().GetStorage()[0], 8);

    UInt8 m(2), n(8); // 2^8 = 256, overflows UInt8
    auto checked_pow_result2 = m.CheckedPow(n);
    ASSERT_FALSE(checked_pow_result2.has_value());

    UInt8 o(0), p(0); // 0^0 = 1
    auto checked_pow_result3 = o.CheckedPow(p);
    ASSERT_TRUE(checked_pow_result3.has_value());
    ASSERT_EQ(checked_pow_result3.value().GetStorage()[0], 1);

    UInt8 q(0), r(5); // 0^5 = 0
    auto checked_pow_result4 = q.CheckedPow(r);
    ASSERT_TRUE(checked_pow_result4.has_value());
    ASSERT_EQ(checked_pow_result4.value().GetStorage()[0], 0);
}
TEST(ArbitraryUnsignedIntTest, WideningMultiplication) {
    using UInt64 = ArbitraryUnsignedInt<64, 0, CPUStorageProvider>;
    using UInt128 = ArbitraryUnsignedInt<128, 0, CPUStorageProvider>;

    // Test case 1: Small numbers
    UInt64 a1(10);
    UInt64 b1(5);
    UInt128 result1 = WideningMul(a1, b1);
    ASSERT_EQ(result1.GetStorage()[0], 50); // 50 in little endian
    for (size_t i = 1; i < 16; ++i) {
        ASSERT_EQ(result1.GetStorage()[i], 0);
    }

    // Test case 2: Larger numbers, result fits in 64 bits
    UInt64 a2(0xFFFFFFFFFFFFFFFFULL); // Max UInt64
    UInt64 b2(2);
    UInt128 result2 = WideningMul(a2, b2);
    // (2^64 - 1) * 2 = 2^65 - 2
    // In 128 bits, this is 0x1FFFFFFFFFFFFFFFE
    ASSERT_EQ(result2.GetStorage()[0], 0xFE); // LSB
    ASSERT_EQ(result2.GetStorage()[1], 0xFF);
    ASSERT_EQ(result2.GetStorage()[2], 0xFF);
    ASSERT_EQ(result2.GetStorage()[3], 0xFF);
    ASSERT_EQ(result2.GetStorage()[4], 0xFF);
    ASSERT_EQ(result2.GetStorage()[5], 0xFF);
    ASSERT_EQ(result2.GetStorage()[6], 0xFF);
    ASSERT_EQ(result2.GetStorage()[7], 0xFF); // MSB of lower 64 bits
    ASSERT_EQ(result2.GetStorage()[8], 0x01); // LSB of upper 64 bits
    for (size_t i = 9; i < 16; ++i) {
        ASSERT_EQ(result2.GetStorage()[i], 0);
    }

    // Test case 3: Two large numbers, result requires 128 bits
    UInt64 a3(0xFFFFFFFFFFFFFFFFULL); // Max UInt64
    UInt64 b3(0xFFFFFFFFFFFFFFFFULL); // Max UInt64
    UInt128 result3 = WideningMul(a3, b3);
    // (2^64 - 1) * (2^64 - 1) = 2^128 - 2*2^64 + 1
    // In 128 bits, this is 0xFFFFFFFFFFFFFFFE0000000000000001
    ASSERT_EQ(result3.GetStorage()[0], 0x01); // LSB
    ASSERT_EQ(result3.GetStorage()[1], 0x00);
    ASSERT_EQ(result3.GetStorage()[2], 0x00);
    ASSERT_EQ(result3.GetStorage()[3], 0x00);
    ASSERT_EQ(result3.GetStorage()[4], 0x00);
    ASSERT_EQ(result3.GetStorage()[5], 0x00);
    ASSERT_EQ(result3.GetStorage()[6], 0x00);
    ASSERT_EQ(result3.GetStorage()[7], 0x00);
    ASSERT_EQ(result3.GetStorage()[8], 0xFE);
    ASSERT_EQ(result3.GetStorage()[9], 0xFF);
    ASSERT_EQ(result3.GetStorage()[10], 0xFF);
    ASSERT_EQ(result3.GetStorage()[11], 0xFF);
    ASSERT_EQ(result3.GetStorage()[12], 0xFF);
    ASSERT_EQ(result3.GetStorage()[13], 0xFF);
    ASSERT_EQ(result3.GetStorage()[14], 0xFF);
    ASSERT_EQ(result3.GetStorage()[15], 0xFF); // MSB
}

TEST(ArbitraryUnsignedIntTest, ToStringTest) {
    using UInt8 = ArbitraryUnsignedInt<8, 0, CPUStorageProvider>;
    using UInt16 = ArbitraryUnsignedInt<16, 0, CPUStorageProvider>;
    using UInt32 = ArbitraryUnsignedInt<32, 0, CPUStorageProvider>;
    using UInt64 = ArbitraryUnsignedInt<64, 0, CPUStorageProvider>;
    using UInt128 = ArbitraryUnsignedInt<128, 0, CPUStorageProvider>;
    using UInt256 = ArbitraryUnsignedInt<256, 0, CPUStorageProvider>;
    UInt8 a(0);
    UInt16 b(12'345);
    UInt32 c(1'234'567'890);
    UInt64 d(1'234'567'890'987'654'321);
    UInt128 e("1234567890987654321234567890987654");
    UInt256 f("1234567890987654321234567890987654321012345678909876543210123456");
    auto expected = std::array<uint8_t, 32>{ 0, 0, 0, 0, 0, 3, 0, 70, 3, 24, 44, 192, 85, 48, 131, 141, 156, 10, 137, 34, 123, 20, 207, 90, 44, 216, 101, 251, 127, 247, 240, 192 };
    ASSERT_EQ(f.ToBeBytes(), expected);
    ASSERT_EQ(a.ToString(), "0");
    ASSERT_EQ(b.ToString(), "12345");
    ASSERT_EQ(c.ToString(), "1234567890");
    ASSERT_EQ(d.ToString(), "1234567890987654321");
    ASSERT_EQ(e.ToString(), "1234567890987654321234567890987654");
    ASSERT_EQ(f.ToString(), "1234567890987654321234567890987654321012345678909876543210123456");
}

TEST(ArbitraryUnsignedIntTest, ComparisonOperators) {
    using UInt8 = ArbitraryUnsignedInt<8, 0, CPUStorageProvider>;

    UInt8 a(10), b(20), c(10);

    // operator==
    ASSERT_TRUE(a == c);
    ASSERT_FALSE(a == b);

    // operator!=
    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a != c);

    // operator<
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(a < c);
    ASSERT_FALSE(b < a);

    // operator<=
    ASSERT_TRUE(a <= b);
    ASSERT_TRUE(a <= c);
    ASSERT_FALSE(b <= a);

    // operator>
    ASSERT_TRUE(b > a);
    ASSERT_FALSE(a > b);
    ASSERT_FALSE(a > c);

    // operator>=
    ASSERT_TRUE(b >= a);
    ASSERT_TRUE(a >= c);
    ASSERT_FALSE(a >= b);

    // Test with different bit sizes (should be handled by conversion operators)
    using UInt16 = ArbitraryUnsignedInt<16, 0, CPUStorageProvider>;
    UInt16 d(10 + 256 * 100);
    ASSERT_TRUE(a == static_cast<UInt8>(d)); // d should promote to UInt8(10).
    ASSERT_TRUE(static_cast<UInt16>(a) != d); // a should promote to UInt16(10).
    ASSERT_TRUE(static_cast<UInt16>(a) <= d);
    ASSERT_TRUE(static_cast<UInt16>(a) < UInt16(11));
    ASSERT_TRUE(UInt16(9) < static_cast<UInt16>(a));

    // Test with max values
    UInt8 max_val = UInt8::Max();
    UInt8 max_minus_one = UInt8(254);
    ASSERT_TRUE(max_val > max_minus_one);
    ASSERT_TRUE(max_val >= max_minus_one);
    ASSERT_FALSE(max_val < max_minus_one);
    ASSERT_FALSE(max_val <= max_minus_one);
}
