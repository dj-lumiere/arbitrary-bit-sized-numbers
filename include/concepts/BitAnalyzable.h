//
// Created by Lumi on 25. 6. 20.
//

#ifndef BITANALYZABLE_H
#define BITANALYZABLE_H
#include "BitAccessible.h"
#include "ByteAnalyzable.h"

template<typename T>
concept BitAnalyzable = BitAccessible<T> && ByteAnalyzable<T> && requires(const T ct, size_t start, size_t count, bool expected) {
    // Counting operations
    { ct.PopCount() } -> std::convertible_to<size_t>;
    { ct.CountLeadingZeros() } -> std::convertible_to<size_t>;
    { ct.CountTrailingZeros() } -> std::convertible_to<size_t>;
    { ct.CountLeadingOnes() } -> std::convertible_to<size_t>;
    { ct.CountTrailingOnes() } -> std::convertible_to<size_t>;
    
    // Pattern searching
    { ct.FindFirstSet() } -> std::convertible_to<std::optional<size_t>>;
    { ct.FindFirstClear() } -> std::convertible_to<std::optional<size_t>>;
    { ct.FindLastSet() } -> std::convertible_to<std::optional<size_t>>;
    { ct.FindLastClear() } -> std::convertible_to<std::optional<size_t>>;
    
    // Pattern testing
    { ct.IsAllZeros() } -> std::convertible_to<bool>;
    { ct.IsAllOnes() } -> std::convertible_to<bool>;
    { ct.IsPowerOfTwo() } -> std::convertible_to<bool>;
    { ct.HasEvenParity() } -> std::convertible_to<bool>;
    { ct.HasOddParity() } -> std::convertible_to<bool>;
    
    // Range testing
    { ct.TestBitRange(start, count, expected) } -> std::convertible_to<bool>;
};

#endif //BITANALYZABLE_H
