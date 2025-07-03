//
// Created by Lumi on 25. 6. 20.
//

#ifndef BYTEANALYZABLE_H
#define BYTEANALYZABLE_H
#include <optional>
#include <span>

#include "ByteAccessible.h"

template<typename T>
concept ByteAnalyzable = ByteAccessible<T> && requires(const T ct, std::span<const uint8_t> pattern) {
    // Pattern searching
    { ct.FindByte(uint8_t{}, size_t{}) } -> std::convertible_to<std::optional<size_t>>;
    { ct.FindBytePattern(pattern, size_t{}) } -> std::convertible_to<std::optional<size_t>>;
    
    // Comparison
    { ct.Compare(ct) } -> std::convertible_to<int>;
    { ct.Compare(pattern) } -> std::convertible_to<int>;
    { ct.Equal(ct) } -> std::convertible_to<bool>;
    { ct.Equal(pattern) } -> std::convertible_to<bool>;
    
    // Checksums
    { ct.ComputeCRC32() } -> std::convertible_to<uint32_t>;
    { ct.ComputeHash() } -> std::convertible_to<uint64_t>;
};

#endif //BYTEANALYZABLE_H
