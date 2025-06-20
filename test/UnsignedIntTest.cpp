//
// Created by Lumi on 25. 6. 18.
//
#include <gtest/gtest.h>
#include "ArbitraryUnsignedInt.h"
#include "storage/CPUStorage.h"

class ArbitraryUnsignedIntTest : public ::testing::Test {
protected:
    using UInt8 = UInt8<CPUMemoryPlace>;
    using UInt16 = UInt16<CPUMemoryPlace>;
    using UInt32 = UInt32<CPUMemoryPlace>;
    using UInt64 = UInt64<CPUMemoryPlace>;
    using UInt128 = UInt128<CPUMemoryPlace>;
    using UInt256 = UInt256<CPUMemoryPlace>;
};

TEST_F(ArbitraryUnsignedIntTest, Constructors) {
    UInt8 a;
    EXPECT_TRUE(a.GetStorage().GetByteSize() == 1);
    EXPECT_TRUE(a.GetStorage()[0] == 0x00);

    UInt16 b(128);
    EXPECT_TRUE(b.GetStorage()[0] == 0x80 & b.GetStorage()[1] == 0x00);
}
