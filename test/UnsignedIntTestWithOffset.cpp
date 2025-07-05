
#include <gtest/gtest.h>
#include "../include/core/unsigned-int/ArbitraryUnsignedInt.h"
#include "../include/storage/cpu-storage/CPUStorage.h"
#include <array>

// Test fixture for ArbitraryUnsignedInt with a non-zero bit offset
class ArbitraryUnsignedIntWithOffsetTest : public ::testing::Test {
protected:
    // 8-bit uint with a 4-bit offset. Will occupy bits 4-11 of storage.
    using UInt8_off4 = ArbitraryUnsignedInt<8, 4, CPUStorageProvider>;

    // 12-bit uint with a 2-bit offset. Will occupy bits 2-13 of storage.
    using UInt12_off2 = ArbitraryUnsignedInt<12, 2, CPUStorageProvider>;

    // 24-bit uint with a 7-bit offset. Will occupy bits 7-30 of storage.
    using UInt24_off7 = ArbitraryUnsignedInt<24, 7, CPUStorageProvider>;
};

TEST_F(ArbitraryUnsignedIntWithOffsetTest, ConstructorWithOffset) {
    // Test with UInt8_off4
    UInt8_off4 a(214); // 0b11010110
    ASSERT_EQ(a.ToString(), "214");

    // Test with UInt12_off2
    UInt12_off2 b(2907); // 0b101101011011
    ASSERT_EQ(b.ToString(), "2907");
}

TEST_F(ArbitraryUnsignedIntWithOffsetTest, AdditionWithOffset) {
    // Test with UInt8_off4
    UInt8_off4 a(100);
    UInt8_off4 b(50);
    UInt8_off4 c = a + b;
    ASSERT_EQ(c.ToString(), "150");

    // Test with overflow
    UInt8_off4 d(200);
    UInt8_off4 e(100);
    UInt8_off4 f = d + e; // 300 % 256 = 44
    ASSERT_EQ(f.ToString(), "44");
}

TEST_F(ArbitraryUnsignedIntWithOffsetTest, SubtractionWithOffset) {
    // Test with UInt12_off2
    UInt12_off2 a(1000);
    UInt12_off2 b(350);
    UInt12_off2 c = a - b;
    ASSERT_EQ(c.ToString(), "650");

    // Test with underflow
    UInt12_off2 d(100);
    UInt12_off2 e(200);
    UInt12_off2 f = d - e; // -100 wraps around in 12 bits (2^12 - 100 = 3996)
    ASSERT_EQ(f.ToString(), "3996");
}

TEST_F(ArbitraryUnsignedIntWithOffsetTest, MultiplicationWithOffset) {
    UInt8_off4 a(10);
    UInt8_off4 b(12);
    UInt8_off4 c = a * b;
    ASSERT_EQ(c.ToString(), "120");

    // Test with overflow
    UInt8_off4 d(20);
    UInt8_off4 e(15);
    UInt8_off4 f = d * e; // 300 % 256 = 44
    ASSERT_EQ(f.ToString(), "44");
}

TEST_F(ArbitraryUnsignedIntWithOffsetTest, DivisionWithOffset) {
    UInt12_off2 a(1000);
    UInt12_off2 b(10);
    UInt12_off2 c = a / b;
    ASSERT_EQ(c.ToString(), "100");

    UInt12_off2 d(100);
    UInt12_off2 e(13);
    UInt12_off2 f = d / e; // 100 / 13 = 7
    ASSERT_EQ(f.ToString(), "7");
}
