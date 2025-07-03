//
// Created by Lumi on 25. 6. 20.
//

#ifndef BYTEACCESSIBLE_H
#define BYTEACCESSIBLE_H
#include <concepts>
#include <cstdint>

template<typename T>
concept ByteAccessible = requires(T t, const T ct, size_t index, uint8_t value) {
    // Individual byte access
    { t[index] } -> std::convertible_to<uint8_t&>;
    { ct[index] } -> std::convertible_to<const uint8_t&>;
    { t.Data() } -> std::convertible_to<uint8_t*>;
    { ct.Data() } -> std::convertible_to<const uint8_t*>;
    
    // Size information
    { ct.GetByteSize() } -> std::convertible_to<size_t>;
    
    // Bulk operations
    { t.Fill(value) } -> std::same_as<void>;
    { t.Clear() } -> std::same_as<void>;
};

#endif //BYTEACCESSIBLE_H
