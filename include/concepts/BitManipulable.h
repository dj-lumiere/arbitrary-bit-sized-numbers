//
// Created by Lumi on 25. 6. 20.
//

#ifndef BITMANIPULABLE_H
#define BITMANIPULABLE_H
#include "BitAnalyzable.h"
#include "BitCopyable.h"

template<typename T>
concept BitManipulable = BitAnalyzable<T> && BitCopyable<T> && requires(T t, const T ct, size_t positions) {
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
};

#endif //BITMANIPULABLE_H
