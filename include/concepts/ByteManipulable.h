//
// Created by Lumi on 25. 6. 20.
//

#ifndef BYTEMANIPULABLE_H
#define BYTEMANIPULABLE_H
#include <cstdint>
#include <concepts>

template<typename T>
concept ByteManipulable = requires(T t, const T ct, size_t index1, size_t index2, 
                                  size_t positions, uint8_t fill_value) {
    // Byte operations
    { t.SwapBytes(index1, index2) } -> std::same_as<void>;
    { t.ReverseByteOrder() } -> std::same_as<void>;
    { t.ShiftBytesLeft(positions) } -> std::same_as<void>;
    { t.ShiftBytesRight(positions) } -> std::same_as<void>;
    { t.ShiftBytesLeft(positions, fill_value) } -> std::same_as<void>;
    { t.ShiftBytesRight(positions, fill_value) } -> std::same_as<void>;

    // Endianness conversion
    { t.ToLittleEndian() } -> std::same_as<void>;
    { t.ToBigEndian() } -> std::same_as<void>;
    { t.ToNativeEndian() } -> std::same_as<void>;

    // Byte-wise operations
    { t.BytewiseAnd(ct) } -> std::same_as<void>;
    { t.BytewiseOr(ct) } -> std::same_as<void>;
    { t.BytewiseXor(ct) } -> std::same_as<void>;
    { t.BytewiseNot() } -> std::same_as<void>;
};

#endif //BYTEMANIPULABLE_H
