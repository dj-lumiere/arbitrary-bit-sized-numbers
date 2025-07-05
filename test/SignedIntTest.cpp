//
// Created by Lumi on 25. 6. 16.
//

#include <cstdint>
#include <span>
#include <gtest/gtest.h>

#include "../include/core/signed-int/ArbitrarySignedInt.h"
#include "../include/storage/cpu-storage/CPUStorage.h"

TEST(ArbitrarySignedIntTest, BasicConstruction) {
    ArbitrarySignedInt<8, 0, CPUStorageProvider> a;
    ASSERT_EQ(a, 0);

    ArbitrarySignedInt<16, 0, CPUStorageProvider> b(127);
    ASSERT_EQ(b, 127);

    ArbitrarySignedInt<32, 0, CPUStorageProvider> c(-127);
    ASSERT_EQ(c, -127);

    ArbitrarySignedInt<64, 0, CPUStorageProvider> d("12345");
    ASSERT_EQ(d, 12345);
}
