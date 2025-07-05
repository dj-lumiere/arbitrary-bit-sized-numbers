//
// Created by Lumi on 25. 7. 4.
//
#include <gtest/gtest.h>
#include "../include/storage/cpu-storage/CPUStorage.h"

TEST(CPUStorageTest, OffsetAddAndSub) {
    // Test OffsetAdd(offset, bitWidth, value)
    CPUStorage<1> storage1;
    storage1.data_[0] = 0b00001111; // 15
    storage1.OffsetAdd(0, 4, 0b00000001); // Add 1 to the lower 4 bits (0b1111 + 0b0001 = 0b0000 with carry)
    // The lower 4 bits should become 0b0000. The upper 4 bits should remain unchanged.
    ASSERT_EQ(storage1.data_[0], 0b00000000);

    CPUStorage<1> storage2;
    storage2.data_[0] = 0b11110000; // 240 (upper 4 bits are 0b1111, lower 4 are 0b0000)
    storage2.OffsetAdd(4, 4, 0b00000001); // Add 1 to the upper 4 bits (0b1111 + 0b0001 = 0b0000 with carry)
    // The upper 4 bits should become 0b0000. The lower 4 bits should remain unchanged.
    ASSERT_EQ(storage2.data_[0], 0b00000000);

    // Test OffsetSub(offset, bitWidth, value)
    CPUStorage<1> storage3;
    storage3.data_[0] = 0b00010000; // 16 (lower 4 bits are 0b0000, upper 4 are 0b0001)
    storage3.OffsetSub(0, 4, 0b00000001); // Subtract 1 from the lower 4 bits (0b0000 - 0b0001 = 0b1111 with borrow)
    // The lower 4 bits should become 0b1111. The upper 4 bits should remain unchanged.
    ASSERT_EQ(storage3.data_[0], 0b00011111);

    CPUStorage<1> storage4;
    storage4.data_[0] = 0b00000000; // 0
    storage4.OffsetSub(4, 4, 0b00000001); // Subtract 1 from the upper 4 bits (0b0000 - 0b0001 = 0b1111 with borrow)
    // The upper 4 bits should become 0b1111. The lower 4 bits should remain unchanged.
    ASSERT_EQ(storage4.data_[0], 0b11110000);

    // Test OffsetAdd(const CPUStorage& ct, srcStart, srcWidth, dstStart)
    CPUStorage<2> storage5;
    storage5.data_[0] = 0x01;
    storage5.data_[1] = 0x00;
    CPUStorage<1> source5;
    source5.data_[0] = 0x01;
    storage5.OffsetAdd(source5, 0, 8, 0); // Add 0x01 to storage5 at offset 0 with width 8
    ASSERT_EQ(storage5.data_[0], 0x02);
    ASSERT_EQ(storage5.data_[1], 0x00); // Should remain unchanged

    CPUStorage<2> storage6;
    storage6.data_[0] = 0xFF;
    storage6.data_[1] = 0xFF; // This byte should remain unchanged
    CPUStorage<1> source6;
    source6.data_[0] = 0x01;
    storage6.OffsetAdd(source6, 0, 8, 0); // Add 0x01 to storage6 at offset 0 with width 8 (overflow)
    ASSERT_EQ(storage6.data_[0], 0x00); // 0xFF + 0x01 = 0x00 (wrapped)
    ASSERT_EQ(storage6.data_[1], 0xFF); // Should remain unchanged

    // Test OffsetSub(const CPUStorage& ct, srcStart, srcWidth, dstStart)
    CPUStorage<2> storage7;
    storage7.data_[0] = 0x02;
    storage7.data_[1] = 0x00;
    CPUStorage<1> source7;
    source7.data_[0] = 0x01;
    storage7.OffsetSub(source7, 0, 8, 0); // Subtract 0x01 from storage7 at offset 0 with width 8
    ASSERT_EQ(storage7.data_[0], 0x01);
    ASSERT_EQ(storage7.data_[1], 0x00); // Should remain unchanged

    CPUStorage<2> storage8;
    storage8.data_[0] = 0x00;
    storage8.data_[1] = 0x00; // This byte should remain unchanged
    CPUStorage<1> source8;
    source8.data_[0] = 0x01;
    storage8.OffsetSub(source8, 0, 8, 0); // Subtract 0x01 from storage8 at offset 0 with width 8 (underflow)
    ASSERT_EQ(storage8.data_[0], 0xFF); // 0x00 - 0x01 = 0xFF (wrapped)
    ASSERT_EQ(storage8.data_[1], 0x00); // Should remain unchanged
}

TEST(CPUStorageTest, OffsetAddWithCarryAndSubWithBorrow) {
    // Test OffsetAddWithCarry(offset, bitWidth, value, initialCarry)
    CPUStorage<1> storage1;
    storage1.data_[0] = 0b00001111; // 15
    auto result1 = storage1.OffsetAddWithCarry(0, 4, 0b00000001, false);
    ASSERT_EQ(result1.first.data_[0], 0b00000000);
    ASSERT_TRUE(result1.second); // Carry should be true

    auto result2 = storage1.OffsetAddWithCarry(0, 4, 0b00000001, true);
    ASSERT_EQ(result2.first.data_[0], 0b00000001);
    ASSERT_TRUE(result2.second); // Carry should be true

    // Test OffsetSubWithBorrow(offset, bitWidth, value, initialBorrow)
    CPUStorage<1> storage3;
    storage3.data_[0] = 0b00010000; // 16
    auto result3 = storage3.OffsetSubWithBorrow(0, 4, 0b00000001, false);
    ASSERT_EQ(result3.first.data_[0], 0b00011111);
    ASSERT_TRUE(result3.second); // Borrow should be true

    auto result4 = storage3.OffsetSubWithBorrow(0, 4, 0b00000001, true);
    ASSERT_EQ(result4.first.data_[0], 0b00011110);
    ASSERT_TRUE(result4.second); // Borrow should be true

    // Test OffsetAddWithCarry(const CPUStorage& ct, srcStart, srcWidth, dstStart, initialCarry)
    CPUStorage<2> storage5;
    storage5.data_[0] = 0xFF;
    storage5.data_[1] = 0x00;
    CPUStorage<1> source5;
    source5.data_[0] = 0x01;
    auto result5 = storage5.OffsetAddWithCarry(source5, 0, 8, 0, false);
    ASSERT_EQ(result5.first.data_[0], 0x00);
    ASSERT_EQ(result5.first.data_[1], 0x00);
    ASSERT_TRUE(result5.second); // Carry should be true

    auto result6 = storage5.OffsetAddWithCarry(source5, 0, 8, 0, true);
    ASSERT_EQ(result6.first.data_[0], 0x01);
    ASSERT_EQ(result6.first.data_[1], 0x00);
    ASSERT_TRUE(result6.second); // Carry should be true

    // Test OffsetSubWithBorrow(const CPUStorage& ct, srcStart, srcWidth, dstStart, initialBorrow)
    CPUStorage<2> storage7;
    storage7.data_[0] = 0x00;
    storage7.data_[1] = 0x00;
    CPUStorage<1> source7;
    source7.data_[0] = 0x01;
    auto result7 = storage7.OffsetSubWithBorrow(source7, 0, 8, 0, false);
    ASSERT_EQ(result7.first.data_[0], 0xFF);
    ASSERT_EQ(result7.first.data_[1], 0x00);
    ASSERT_TRUE(result7.second); // Borrow should be true

    auto result8 = storage7.OffsetSubWithBorrow(source7, 0, 8, 0, true);
    ASSERT_EQ(result8.first.data_[0], 0xFE);
    ASSERT_EQ(result8.first.data_[1], 0x00);
    ASSERT_TRUE(result8.second); // Borrow should be true
}

TEST(CPUStorageTest, BitAccessible) {
    CPUStorage<1> storage;

    // Test GetBit and SetBit
    storage.SetBit(0);
    ASSERT_TRUE(storage.GetBit(0));
    ASSERT_FALSE(storage.GetBit(1));

    // Test SetBit with value
    storage.SetBit(1, true);
    ASSERT_TRUE(storage.GetBit(1));
    storage.SetBit(0, false);
    ASSERT_FALSE(storage.GetBit(0));

    // Test ClearBit
    storage.ClearBit(1);
    ASSERT_FALSE(storage.GetBit(1));

    // Test FlipBit
    storage.FlipBit(2);
    ASSERT_TRUE(storage.GetBit(2));
    storage.FlipBit(2);
    ASSERT_FALSE(storage.GetBit(2));

    // Test SetAllBits
    storage.SetAllBits();
    for (size_t i = 0; i < storage.GetBitSize(); ++i) {
        ASSERT_TRUE(storage.GetBit(i));
    }

    // Test ClearAllBits
    storage.ClearAllBits();
    for (size_t i = 0; i < storage.GetBitSize(); ++i) {
        ASSERT_FALSE(storage.GetBit(i));
    }

    // Test FlipAllBits
    storage.FlipAllBits();
    for (size_t i = 0; i < storage.GetBitSize(); ++i) {
        ASSERT_TRUE(storage.GetBit(i));
    }
    storage.FlipAllBits();
    for (size_t i = 0; i < storage.GetBitSize(); ++i) {
        ASSERT_FALSE(storage.GetBit(i));
    }
}

TEST(CPUStorageTest, BitAnalyzable) {
    CPUStorage<2> storage; // 16 bits
    storage.data_[0] = 0b11010110; // 8 bits
    storage.data_[1] = 0b00101101; // 8 bits

    // PopCount
    ASSERT_EQ(storage.PopCount(), 9);

    // CountLeadingZeros
    storage.ClearAllBits();
    storage.SetBit(10); // 0b00000100 00000000
    ASSERT_EQ(storage.CountLeadingZeros(), 5);

    // CountTrailingZeros
    storage.ClearAllBits();
    storage.SetBit(5); // 0b00100000
    ASSERT_EQ(storage.CountTrailingZeros(), 5);

    // CountLeadingOnes
    storage.SetAllBits();
    storage.ClearBit(10); // 0b11111011 11111111
    ASSERT_EQ(storage.CountLeadingOnes(), 5);

    // CountTrailingOnes
    storage.SetAllBits();
    storage.ClearBit(5); // 0b11111111 11011111
    ASSERT_EQ(storage.CountTrailingOnes(), 5);

    // FindFirstSet
    storage.ClearAllBits();
    storage.SetBit(5);
    ASSERT_EQ(storage.FindFirstSet().value(), 5);
    storage.ClearAllBits();
    ASSERT_FALSE(storage.FindFirstSet().has_value());

    // FindFirstClear
    storage.SetAllBits();
    storage.ClearBit(5);
    ASSERT_EQ(storage.FindFirstClear().value(), 5);
    storage.SetAllBits();
    ASSERT_FALSE(storage.FindFirstClear().has_value());

    // FindLastSet
    storage.ClearAllBits();
    storage.SetBit(10);
    ASSERT_EQ(storage.FindLastSet().value(), 10);
    storage.ClearAllBits();
    ASSERT_FALSE(storage.FindLastSet().has_value());

    // FindLastClear
    storage.SetAllBits();
    storage.ClearBit(10);
    ASSERT_EQ(storage.FindLastClear().value(), 10);
    storage.SetAllBits();
    ASSERT_FALSE(storage.FindLastClear().has_value());

    // IsAllZeros
    storage.ClearAllBits();
    ASSERT_TRUE(storage.IsAllZeros());
    storage.SetBit(0);
    ASSERT_FALSE(storage.IsAllZeros());

    // IsAllOnes
    storage.SetAllBits();
    ASSERT_TRUE(storage.IsAllOnes());
    storage.ClearBit(0);
    ASSERT_FALSE(storage.IsAllOnes());

    // IsPowerOfTwo
    storage.ClearAllBits();
    storage.SetBit(5);
    ASSERT_TRUE(storage.IsPowerOfTwo());
    storage.SetBit(6);
    ASSERT_FALSE(storage.IsPowerOfTwo());

    // HasEvenParity
    storage.ClearAllBits();
    storage.SetBit(0);
    storage.SetBit(1);
    ASSERT_TRUE(storage.HasEvenParity());
    storage.SetBit(2);
    ASSERT_FALSE(storage.HasEvenParity());

    // HasOddParity
    storage.ClearAllBits();
    storage.SetBit(0);
    ASSERT_TRUE(storage.HasOddParity());
    storage.SetBit(1);
    ASSERT_FALSE(storage.HasOddParity());

    // TestBitRange
    storage.ClearAllBits();
    storage.SetBitRange(2, 4); // Set bits 2, 3, 4, 5
    ASSERT_TRUE(storage.TestBitRange(2, 4, true));
    ASSERT_FALSE(storage.TestBitRange(2, 5, true));
    ASSERT_FALSE(storage.TestBitRange(1, 4, true));
    storage.ClearBitRange(3, 2); // Clear bits 3, 4
    ASSERT_TRUE(storage.TestBitRange(3, 2, false));
}

TEST(CPUStorageTest, BitCopyable) {
    CPUStorage<2> storage;
    storage.SetBitRange(0, 8); // Set first 8 bits

    // CopyBitsInternal
    storage.CopyBitsInternal(0, 4, 8);
    ASSERT_TRUE(storage.TestBitRange(8, 4, true));
    ASSERT_TRUE(storage.TestBitRange(12, 4, false));

    // MoveBitsInternal
    storage.ClearAllBits();
    storage.SetBitRange(0, 4);
    storage.MoveBitsInternal(0, 4, 2); // Overlapping move
    ASSERT_TRUE(storage.TestBitRange(2, 4, true));
    ASSERT_TRUE(storage.TestBitRange(0, 2, false));

    // CopyBitsFrom
    CPUStorage<1> source;
    source.SetAllBits();
    storage.ClearAllBits();
    storage.CopyBitsFrom(source, 0, 8, 4);
    ASSERT_TRUE(storage.TestBitRange(4, 8, true));
    ASSERT_TRUE(storage.TestBitRange(0, 4, false));
    ASSERT_TRUE(storage.TestBitRange(12, 4, false));

    // CopyBitsTo
    CPUStorage<1> dest;
    storage.ClearAllBits();
    storage.SetBitRange(2, 8);
    storage.CopyBitsTo(dest, 2, 8, 0);
    ASSERT_TRUE(dest.TestBitRange(0, 8, true));

    // SetBitRange
    storage.ClearAllBits();
    storage.SetBitRange(5, 6);
    for (int i = 5; i < 11; ++i) {
        ASSERT_TRUE(storage.GetBit(i));
    }
    ASSERT_FALSE(storage.GetBit(4));
    ASSERT_FALSE(storage.GetBit(11));

    // ClearBitRange
    storage.SetAllBits();
    storage.ClearBitRange(3, 7);
    for (int i = 3; i < 10; ++i) {
        ASSERT_FALSE(storage.GetBit(i));
    }
    ASSERT_TRUE(storage.GetBit(2));
    ASSERT_TRUE(storage.GetBit(10));

    // FlipBitRange
    storage.ClearAllBits();
    storage.FlipBitRange(4, 5);
    for (int i = 4; i < 9; ++i) {
        ASSERT_TRUE(storage.GetBit(i));
    }
    storage.FlipBitRange(6, 5);
    ASSERT_TRUE(storage.GetBit(4));
    ASSERT_TRUE(storage.GetBit(5));
    ASSERT_FALSE(storage.GetBit(6));
    ASSERT_FALSE(storage.GetBit(7));
    ASSERT_FALSE(storage.GetBit(8));
    ASSERT_TRUE(storage.GetBit(9));
    ASSERT_TRUE(storage.GetBit(10));
}

TEST(CPUStorageTest, BitManipulable) {
    CPUStorage<2> storage; // 16 bits
    CPUStorage<4> storage2; // 32 bits

    // ShiftLeft
    storage.ClearAllBits();
    storage.SetBit(0); // 0x01
    storage.ShiftLeft(1);
    ASSERT_EQ(storage.GetBit(1), true);
    ASSERT_EQ(storage.GetBit(0), false);
    storage.ShiftLeft(8); // Now at bit 9
    ASSERT_EQ(storage.data_[1], 0b00000010); // Bit 9 is the 2nd bit of the 2nd byte
    ASSERT_EQ(storage.data_[0], 0);

    storage.data_[0] = 0b11001100;
    storage.data_[1] = 0b00110011;
    storage.ShiftLeft(2); //0011001111001100 -> 1100111100110000
    ASSERT_EQ(storage.data_[1], 0b11001111);
    ASSERT_EQ(storage.data_[0], 0b00110000);

    storage2.data_[0] = 0b11001100;
    storage2.data_[1] = 0b00110011;
    storage2.data_[2] = 0b11110000;
    storage2.data_[3] = 0b00001111;
    storage2.ShiftLeft(12); // 00001111111100000011001111001100 -> 00000011 00111100 11000000 00000000
    ASSERT_EQ(storage2.data_[3], 0b00000011);
    ASSERT_EQ(storage2.data_[2], 0b00111100);
    ASSERT_EQ(storage2.data_[1], 0b11000000);
    ASSERT_EQ(storage2.data_[0], 0b00000000);

    // ShiftRight
    storage.ClearAllBits();
    storage.SetBit(15);
    storage.ShiftRight(1);
    ASSERT_EQ(storage.GetBit(14), true);
    ASSERT_EQ(storage.GetBit(15), false);
    storage.ShiftRight(8); // Now at bit 6
    ASSERT_EQ(storage.data_[0], 0b01000000);
    ASSERT_EQ(storage.data_[1], 0);

    storage.data_[0] = 0b11001100;
    storage.data_[1] = 0b00110011;
    storage.ShiftRight(2); // 0011001111001100 -> 00001100 11110011
    ASSERT_EQ(storage.data_[1], 0b00001100);
    ASSERT_EQ(storage.data_[0], 0b11110011);

    storage2.ClearAllBits();
    storage2.data_[0] = 0b11001100;
    storage2.data_[1] = 0b00110011;
    storage2.data_[2] = 0b11110000;
    storage2.data_[3] = 0b00001111;
    storage2.ShiftRight(12); // 00001111111100000011001111001100 -> 00000000 00000000 11111111 00000011
    ASSERT_EQ(storage2.data_[3], 0b00000000);
    ASSERT_EQ(storage2.data_[2], 0b00000000);
    ASSERT_EQ(storage2.data_[1], 0b11111111);
    ASSERT_EQ(storage2.data_[0], 0b00000011);

    // RotateLeft
    storage.ClearAllBits();
    storage.data_[0] = 0b10000000;
    storage.data_[1] = 0b00000001; // Bit 8 and bit 7 are set
    storage.RotateLeft(1);
    ASSERT_EQ(storage.data_[0], 0b00000000); // Bit 7 shifted to bit 8, bit 15 wrapped to bit 0
    ASSERT_EQ(storage.data_[1], 0b00000011);

    // RotateRight
    storage.ClearAllBits();
    storage.data_[0] = 0b00000001; // Bit 0
    storage.data_[1] = 0b10000000; // Bit 15
    storage.RotateRight(1);
    ASSERT_EQ(storage.data_[0], 0b00000000); // Bit 0 wrapped to bit 15
    ASSERT_EQ(storage.data_[1], 0b11000000); // Bit 15 shifted to bit 14

    // ReverseBits
    storage.ClearAllBits();
    storage.data_[0] = 0b11001010;
    storage.ReverseBits();
    ASSERT_EQ(storage.data_[1], 0b01010011); // Reversed of first byte
    ASSERT_EQ(storage.data_[0], 0); // Second byte was 0, reversed is 0

    // ReverseBytes
    storage.ClearAllBits();
    storage.data_[0] = 0x12;
    storage.data_[1] = 0x34;
    storage.ReverseBytes();
    ASSERT_EQ(storage.data_[0], 0x34);
    ASSERT_EQ(storage.data_[1], 0x12);

    // BitwiseAnd, Or, Xor, Not
    CPUStorage<1> s1, s2;
    s1.data_[0] = 0b10101010;
    s2.data_[0] = 0b01010101;
    s1.BitwiseAnd(s2);
    ASSERT_EQ(s1.data_[0], 0);
    s1.data_[0] = 0b10101010;
    s1.BitwiseOr(s2);
    ASSERT_EQ(s1.data_[0], 0xFF);
    s1.data_[0] = 0b10101010;
    s1.BitwiseXor(s2);
    ASSERT_EQ(s1.data_[0], 0xFF);
    s1.BitwiseNot();
    ASSERT_EQ(s1.data_[0], 0);

    // Increment, Decrement
    storage.ClearAllBits();
    storage.Increment();
    ASSERT_EQ(storage.data_[0], 1);
    storage.data_[0] = 0xFF;
    storage.Increment();
    ASSERT_EQ(storage.data_[0], 0);
    ASSERT_EQ(storage.data_[1], 1);
    storage.Decrement();
    ASSERT_EQ(storage.data_[0], 0xFF);
    ASSERT_EQ(storage.data_[1], 0);
    storage.Decrement();
    ASSERT_EQ(storage.data_[0], 0xFE);
}

TEST(CPUStorageTest, ByteAccessible) {
    CPUStorage<4> storage;
    storage[0] = 0x11;
    storage[1] = 0x22;
    storage[2] = 0x33;
    storage[3] = 0x44;

    // Operator[]
    ASSERT_EQ(storage[0], 0x11);
    ASSERT_EQ(storage[1], 0x22);

    // Data()
    uint8_t* dataPtr = storage.Data();
    ASSERT_EQ(dataPtr[2], 0x33);
    dataPtr[3] = 0x55;
    ASSERT_EQ(storage[3], 0x55);

    // GetByteSize
    ASSERT_EQ(storage.GetByteSize(), 4);

    // Fill
    storage.Fill(0xAA);
    for (size_t i = 0; i < storage.GetByteSize(); ++i) {
        ASSERT_EQ(storage[i], 0xAA);
    }

    // Clear
    storage.Clear();
    for (size_t i = 0; i < storage.GetByteSize(); ++i) {
        ASSERT_EQ(storage[i], 0);
    }
}

TEST(CPUStorageTest, ByteAnalyzable) {
    CPUStorage<8> storage;
    for (size_t i = 0; i < 8; ++i) {
        storage[i] = i + 1; // 1, 2, 3, 4, 5, 6, 7, 8
    }

    // FindByte
    ASSERT_EQ(storage.FindByte(3).value(), 2);
    ASSERT_FALSE(storage.FindByte(9).has_value());
    ASSERT_EQ(storage.FindByte(3, 3).has_value(), false);

    // FindBytePattern
    uint8_t pattern1[] = { 3, 4, 5 };
    ASSERT_EQ(storage.FindBytePattern(pattern1).value(), 2);
    uint8_t pattern2[] = { 3, 5 };
    ASSERT_FALSE(storage.FindBytePattern(pattern2).has_value());

    // Compare
    CPUStorage<8> same, different;
    for (size_t i = 0; i < 8; ++i) {
        same[i] = i + 1;
        different[i] = i + 2;
    }
    ASSERT_EQ(storage.Compare(same), 0);
    ASSERT_NE(storage.Compare(different), 0);

    // Equal
    ASSERT_TRUE(storage.Equal(same));
    ASSERT_FALSE(storage.Equal(different));
}

TEST(CPUStorageTest, ByteCopyable) {
    CPUStorage<8> storage;
    for (size_t i = 0; i < 8; ++i) {
        storage[i] = i;
    }

    // CopyBytesInternal
    storage.CopyBytesInternal(0, 4, 4); // Copy 0,1,2,3 to 4,5,6,7
    ASSERT_EQ(storage[4], 0);
    ASSERT_EQ(storage[5], 1);
    ASSERT_EQ(storage[6], 2);
    ASSERT_EQ(storage[7], 3);

    // MoveBytesInternal
    for (size_t i = 0; i < 8; ++i)
        storage[i] = i;
    storage.MoveBytesInternal(0, 4, 2); // Move 0,1,2,3 to 2,3,4,5
    ASSERT_EQ(storage[2], 0);
    ASSERT_EQ(storage[3], 1);
    ASSERT_EQ(storage[4], 2);
    ASSERT_EQ(storage[5], 3);

    // CopyBytesFrom
    CPUStorage<4> source;
    for (size_t i = 0; i < 4; ++i)
        source[i] = 10 + i;
    storage.CopyBytesFrom(source, 0, 4, 2);
    ASSERT_EQ(storage[2], 10);
    ASSERT_EQ(storage[3], 11);
    ASSERT_EQ(storage[4], 12);
    ASSERT_EQ(storage[5], 13);

    // CopyBytesTo
    CPUStorage<4> dest;
    for (size_t i = 0; i < 8; ++i)
        storage[i] = i;
    storage.CopyBytesTo(dest, 2, 4, 0);
    ASSERT_EQ(dest[0], 2);
    ASSERT_EQ(dest[1], 3);
    ASSERT_EQ(dest[2], 4);
    ASSERT_EQ(dest[3], 5);

    // CopyFromBytes
    uint8_t bytes[] = { 20, 21, 22, 23 };
    storage.CopyFromBytes(bytes, 4, 0, 4, 4);
    ASSERT_EQ(storage[4], 20);
    ASSERT_EQ(storage[5], 21);
    ASSERT_EQ(storage[6], 22);
    ASSERT_EQ(storage[7], 23);

    // CopyToBytes
    uint8_t more_bytes[4];
    storage.CopyToBytes(more_bytes, 4, 4, 0, 4);
    ASSERT_EQ(more_bytes[0], 20);
    ASSERT_EQ(more_bytes[1], 21);
    ASSERT_EQ(more_bytes[2], 22);
    ASSERT_EQ(more_bytes[3], 23);

    // CopyFromSpan
    std::vector<uint8_t> vec = { 30, 31 };
    std::span<const uint8_t> span_const(vec);
    storage.CopyFromSpan(span_const, 0);
    ASSERT_EQ(storage[0], 30);
    ASSERT_EQ(storage[1], 31);

    // CopyToSpan
    std::vector<uint8_t> vec2(2);
    std::span<uint8_t> span_mut(vec2);
    storage.CopyToSpan(span_mut, 0);
    ASSERT_EQ(vec2[0], 30);
    ASSERT_EQ(vec2[1], 31);

    // MoveBytes
    for (size_t i = 0; i < 8; ++i)
        storage[i] = i;
    storage.MoveBytes(0, 2, 4);
    ASSERT_EQ(storage[2], 0);
    ASSERT_EQ(storage[3], 1);
    ASSERT_EQ(storage[4], 2);
    ASSERT_EQ(storage[5], 3);
}

TEST(CPUStorageTest, ByteManipulable) {
    CPUStorage<4> storage;
    storage[0] = 0x11;
    storage[1] = 0x22;
    storage[2] = 0x33;
    storage[3] = 0x44;

    // SwapBytes
    storage.SwapBytes(0, 3);
    ASSERT_EQ(storage[0], 0x44);
    ASSERT_EQ(storage[3], 0x11);

    // ReverseByteOrder
    storage.ReverseByteOrder();
    ASSERT_EQ(storage[0], 0x11);
    ASSERT_EQ(storage[1], 0x33);
    ASSERT_EQ(storage[2], 0x22);
    ASSERT_EQ(storage[3], 0x44);

    // ShiftBytesLeft
    storage.ShiftBytesLeft(1);
    ASSERT_EQ(storage[0], 0x00);
    ASSERT_EQ(storage[1], 0x11);
    ASSERT_EQ(storage[2], 0x33);
    ASSERT_EQ(storage[3], 0x22);

    // ShiftBytesRight
    storage.ShiftBytesRight(1);
    ASSERT_EQ(storage[0], 0x11);
    ASSERT_EQ(storage[1], 0x33);
    ASSERT_EQ(storage[2], 0x22);
    ASSERT_EQ(storage[3], 0x00);

    // ShiftBytesLeft with fill
    storage.ShiftBytesLeft(2, 0xFF);
    ASSERT_EQ(storage[0], 0xFF);
    ASSERT_EQ(storage[1], 0xFF);
    ASSERT_EQ(storage[2], 0x11);
    ASSERT_EQ(storage[3], 0x33);

    // ShiftBytesRight with fill
    storage.ShiftBytesRight(2, 0xEE);
    ASSERT_EQ(storage[0], 0x11);
    ASSERT_EQ(storage[1], 0x33);
    ASSERT_EQ(storage[2], 0xEE);
    ASSERT_EQ(storage[3], 0xEE);

    // BytewiseAnd, Or, Xor, Not
    CPUStorage<1> s1, s2;
    s1[0] = 0xF0;
    s2[0] = 0x0F;
    s1.BytewiseAnd(s2);
    ASSERT_EQ(s1[0], 0x00);
    s1[0] = 0xF0;
    s1.BytewiseOr(s2);
    ASSERT_EQ(s1[0], 0xFF);
    s1[0] = 0xF0;
    s1.BytewiseXor(s2);
    ASSERT_EQ(s1[0], 0xFF);
    s1.BytewiseNot();
    ASSERT_EQ(s1[0], 0x00);
}

TEST(CPUStorageTest, Miscellaneous) {
    // Test Clone
    CPUStorage<4> storage1;
    storage1[0] = 0xDE;
    storage1[1] = 0xAD;
    storage1[2] = 0xBE;
    storage1[3] = 0xEF;
    auto storage2 = storage1.Clone();
    ASSERT_NE(storage1.Data(), storage2->Data()); // Should be a deep copy
    ASSERT_TRUE(storage1.Equal(*storage2));

    // Test CanCopyBits
    CPUStorage<2> source_bits;
    CPUStorage<4> dest_bits;
    ASSERT_TRUE(dest_bits.CanCopyBits(source_bits, 0, 16, 0)); // Full copy
    ASSERT_TRUE(dest_bits.CanCopyBits(source_bits, 0, 8, 24)); // Copy 8 bits to the end
    ASSERT_FALSE(dest_bits.CanCopyBits(source_bits, 0, 17, 0)); // source overflow
    ASSERT_FALSE(dest_bits.CanCopyBits(source_bits, 8, 9, 0)); // source overflow
    ASSERT_FALSE(dest_bits.CanCopyBits(source_bits, 0, 16, 17)); // dest overflow

    // Test Compare with span
    CPUStorage<4> storage_compare;
    storage_compare[0] = 1;
    storage_compare[1] = 2;
    storage_compare[2] = 3;
    storage_compare[3] = 4;
    std::vector<uint8_t> vec_equal = { 1, 2, 3, 4 };
    std::vector<uint8_t> vec_less = { 1, 2, 3, 3 };
    std::vector<uint8_t> vec_greater = { 1, 2, 3, 5 };
    std::vector<uint8_t> vec_short = { 1, 2, 3 };
    ASSERT_EQ(storage_compare.Compare(std::span<const uint8_t>(vec_equal)), 0);
    ASSERT_GT(storage_compare.Compare(std::span<const uint8_t>(vec_less)), 0);
    ASSERT_LT(storage_compare.Compare(std::span<const uint8_t>(vec_greater)), 0);
    // When comparing with a shorter span, it should only compare up to the shorter length
    ASSERT_EQ(storage_compare.Compare(std::span<const uint8_t>(vec_short)), 0);

    // Test Equal with span
    ASSERT_TRUE(storage_compare.Equal(std::span<const uint8_t>(vec_equal)));
    ASSERT_FALSE(storage_compare.Equal(std::span<const uint8_t>(vec_less)));
    ASSERT_FALSE(storage_compare.Equal(std::span<const uint8_t>(vec_short)));

    // Test CanCopyBytes (internal)
    CPUStorage<8> storage_bytes;
    ASSERT_TRUE(storage_bytes.CanCopyBytes(0, 4, 4));
    ASSERT_FALSE(storage_bytes.CanCopyBytes(0, 5, 4)); // Overlap and exceed
    ASSERT_FALSE(storage_bytes.CanCopyBytes(5, 4, 0)); // Exceeds source size

    // Test CanCopyBytes (external)
    CPUStorage<4> source_bytes;
    CPUStorage<8> dest_bytes;
    ASSERT_TRUE(dest_bytes.CanCopyBytes(source_bytes, 0, 4, 0)); // Full copy
    ASSERT_TRUE(dest_bytes.CanCopyBytes(source_bytes, 0, 4, 4)); // Copy to end
    ASSERT_FALSE(dest_bytes.CanCopyBytes(source_bytes, 0, 5, 0)); // Source overflow
    ASSERT_FALSE(dest_bytes.CanCopyBytes(source_bytes, 0, 4, 5)); // Dest overflow

    // Test ToBigEndian
    CPUStorage<4> endian_storage;
    endian_storage[0] = 0x12;
    endian_storage[1] = 0x34;
    endian_storage[2] = 0x56;
    endian_storage[3] = 0x78;
    endian_storage.ToBigEndian(); // This is just ReverseByteOrder
    ASSERT_EQ(endian_storage[0], 0x78);
    ASSERT_EQ(endian_storage[1], 0x56);
    ASSERT_EQ(endian_storage[2], 0x34);
    ASSERT_EQ(endian_storage[3], 0x12);
}
