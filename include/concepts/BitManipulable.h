//
// Created by Lumi on 25. 6. 20.
//

#ifndef BITMANIPULABLE_H
#define BITMANIPULABLE_H
#include "BitAnalyzable.h"
#include "BitCopyable.h"

template<typename T>
concept BitManipulable = BitAnalyzable<T> && BitCopyable<T> && requires(T t, const T ct, size_t positions, size_t offset, size_t bitWidth, size_t value, size_t srcStart, size_t srcWidth, size_t dstStart) {
    // Shifting and rotation
    { t.ShiftLeft(positions) } -> std::same_as<void>;
    { t.ShiftRight(positions) } -> std::same_as<void>;
    { t.RotateLeft(positions) } -> std::same_as<void>;
    { t.RotateRight(positions) } -> std::same_as<void>;
    
    // Bit reversal
    { t.ReverseBits() } -> std::same_as<void>;
    { t.ReverseBytes() } -> std::same_as<void>;
    
    // Bitwise operations
    { t.BitwiseAnd(ct) } -> std::same_as<void>;
    { t.BitwiseOr(ct) } -> std::same_as<void>;
    { t.BitwiseXor(ct) } -> std::same_as<void>;
    { t.BitwiseNot() } -> std::same_as<void>;
    
    // Arithmetic-style operations
    { t.Increment() } -> std::same_as<void>;
    { t.Decrement() } -> std::same_as<void>;
    
    // Simple offset arithmetic (most common use case)
    { t.OffsetAdd(offset, bitWidth, value) } -> std::same_as<void>;
    { t.OffsetSub(offset, bitWidth, value) } -> std::same_as<void>;
    
    // Range-to-range arithmetic (advanced operations)
    { t.OffsetAdd(ct, srcStart, srcWidth, dstStart) } -> std::same_as<void>;
    { t.OffsetSub(ct, srcStart, srcWidth, dstStart) } -> std::same_as<void>;

    // Arithmetic with carry/borrow
    { t.OffsetAddWithCarry(offset, bitWidth, value, false) } -> std::same_as<std::pair<T, bool>>;
    { t.OffsetSubWithBorrow(offset, bitWidth, value, false) } -> std::same_as<std::pair<T, bool>>;
    { t.OffsetAddWithCarry(ct, srcStart, srcWidth, dstStart, false) } -> std::same_as<std::pair<T, bool>>;
    { t.OffsetSubWithBorrow(ct, srcStart, srcWidth, dstStart, false) } -> std::same_as<std::pair<T, bool>>;
};

#endif //BITMANIPULABLE_H
