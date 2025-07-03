//
// Created by Lumi on 25. 6. 18.
//
#include <gtest/gtest.h>
#include "ArbitraryUnsignedInt.h"
#include "storage/CPUStorage.h"

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
    ASSERT_EQ(c.GetStorage()[0], 0x78);
    ASSERT_EQ(c.GetStorage()[1], 0x56);
    ASSERT_EQ(c.GetStorage()[2], 0x34);
    ASSERT_EQ(c.GetStorage()[3], 0x12);

    ArbitraryUnsignedInt<64, 0, CPUStorageProvider> d("12345678901234567890"); // 0xAB54A98CEB1F0AD2
    ASSERT_EQ(d.GetStorage()[0], 0xD2);
    ASSERT_EQ(d.GetStorage()[1], 0x0A);
    ASSERT_EQ(d.GetStorage()[2], 0x1F);
    ASSERT_EQ(d.GetStorage()[3], 0xEB);
    ASSERT_EQ(d.GetStorage()[4], 0x8C);
    ASSERT_EQ(d.GetStorage()[5], 0xA9);
    ASSERT_EQ(d.GetStorage()[6], 0x54);
    ASSERT_EQ(d.GetStorage()[7], 0xAB);
}

TEST(ArbitraryUnsignedIntTest, MemoryLayout) {
    using UInt128 = ArbitraryUnsignedInt<128, 0, CPUStorageProvider>;
    using UInt256 = ArbitraryUnsignedInt<256, 0, CPUStorageProvider>;

    UInt128 e(std::string("340282366920938463463374607431768211455")); // 2^128 - 1
    for (size_t i = 0; i < 16; ++i) {
        EXPECT_EQ(e.GetStorage().data_[i], 0xFF) << "Byte " << i << " of UInt128 e is not 0xFF";
    }

    UInt256 f(std::string("115792089237316195423570985008687907853269984665640564039457584007913129639935")); // 2^256 - 1
    for (size_t i = 0; i < 32; ++i) {
        EXPECT_EQ(f.GetStorage().data_[i], 0xFF) << "Byte " << i << " of UInt256 f is not 0xFF";
    }
}
