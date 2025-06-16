//
// Created by Lumi on 25. 6. 16.
//

#ifndef IBYTEMANIPULABLE_H
#define IBYTEMANIPULABLE_H
#pragma once
#include <cstdint>

class IByteManipulable {
public:
    virtual ~IByteManipulable() = default;

    // Byte operations
    virtual void SwapBytes(size_t index1, size_t index2) = 0;
    virtual void ReverseByteOrder() = 0;
    virtual void ShiftBytesLeft(size_t positions) = 0;
    virtual void ShiftBytesRight(size_t positions) = 0;
    virtual void ShiftBytesLeft(size_t positions, uint8_t fillValue) = 0;
    virtual void ShiftBytesRight(size_t positions, uint8_t fillValue) = 0;

    // Endianness conversion
    virtual void ToLittleEndian() = 0;
    virtual void ToBigEndian() = 0;
    virtual void ToNativeEndian() = 0;

    // Byte-wise operations
    virtual void BytewiseAnd(const IByteManipulable& other) = 0;
    virtual void BytewiseOr(const IByteManipulable& other) = 0;
    virtual void BytewiseXor(const IByteManipulable& other) = 0;
    virtual void BytewiseNot() = 0;
};

#endif //IBYTEMANIPULABLE_H
