//
// Created by Lumi on 25. 6. 16.
//

#ifndef IBITACCESSIBLE_H
#define IBITACCESSIBLE_H
#pragma once

#include "IByteAccessible.h"
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

class IBitAccessible : public IByteAccessible {
public:
    ~IBitAccessible() override = default;

    // Individual bit access
    virtual bool GetBit(const size_t bitIndex) const {
        return (*this)[bitIndex >> 3] & (1 << (bitIndex & 7));
    }
    virtual void SetBit(const size_t bitIndex) {
        (*this)[bitIndex >> 3] |= (1 << (bitIndex & 7));
    }
    
    virtual void SetBit(const size_t bitIndex,
        const bool value) {
        if (value) {
            SetBit(bitIndex);
        }
        else {
            ClearBit(bitIndex);
        }
    }
    
    virtual void ClearBit(const size_t bitIndex) {
        (*this)[bitIndex >> 3] &= ~(1 << (bitIndex & 7));
    }
    virtual void FlipBit(const size_t bitIndex) {
        (*this)[bitIndex >> 3] ^= (1 << (bitIndex & 7));
    }

    // Size information
    virtual size_t GetBitSize() const {
        return GetByteSize() * 8;
    }

    // Bulk operations
    virtual void SetAllBits() {
        this->Fill(0xFF);
    }
    virtual void ClearAllBits() {
        this->Fill(0x00);
    }
    virtual void FlipAllBits() {
        for (size_t i = 0; i < GetByteSize(); ++i) {
            (*this)[i] ^= 0xFF;
        }
    }
};

#endif //IBITMANIPULABLE_H
