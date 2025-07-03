//
// Created by Lumi on 25. 6. 20.
//

#ifndef BITACCESSIBLE_H
#define BITACCESSIBLE_H
#include "ByteAccessible.h"

template<typename T>
concept BitAccessible = ByteAccessible<T> && requires(T t, const T ct, size_t index) {
    // Individual bit access
    { ct.GetBit(index) } -> std::convertible_to<bool>;
    { t.SetBit(index) } -> std::same_as<void>;
    { t.ClearBit(index) } -> std::same_as<void>;
    { t.FlipBit(index) } -> std::same_as<void>;
    
    // Size information
    { ct.GetBitSize() } -> std::convertible_to<size_t>;
    
    // Bulk operations
    { t.SetAllBits() } -> std::same_as<void>;
    { t.ClearAllBits() } -> std::same_as<void>;
    { t.FlipAllBits() } -> std::same_as<void>;
};

#endif //BITACCESSIBLE_H
