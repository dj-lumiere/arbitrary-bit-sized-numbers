//
// Created by Lumi on 25. 6. 16.
//

#ifndef IBITANALYZABLE_H
#define IBITANALYZABLE_H
#pragma once
#include <optional>

#include "IByteAccessible.h"
#include "IByteAnalyzable.h"

class IBitAnalyzable : public IByteAnalyzable, IByteAccessible {
public:
    virtual ~IBitAnalyzable() = default;

    // Counting operations
    virtual size_t PopCount() const {
        size_t result = 0;
        for (size_t i = 0; i < GetByteSize(); ++i) {
            result += __builtin_popcount(this->operator[](i));
        }
        return result;
    }
    
    virtual size_t CountLeadingZeros() const {
        size_t totalBits = GetByteSize() * 8;
        for (size_t i = 0; i < GetByteSize(); ++i) {
            uint8_t byte = this->operator[](i);
            if (byte != 0) {
                return i * 8 + __builtin_clz(byte) - (sizeof(unsigned int) * 8 - 8);
            }
        }
        return totalBits;
    }
    
    virtual size_t CountTrailingZeros() const {
        for (size_t i = GetByteSize(); i > 0; --i) {
            uint8_t byte = this->operator[](i - 1);
            if (byte != 0) {
                return (GetByteSize() - i) * 8 + __builtin_ctz(byte);
            }
        }
        return GetByteSize() * 8;
    }
    
    virtual size_t CountLeadingOnes() const {
        for (size_t i = 0; i < GetByteSize(); ++i) {
            uint8_t byte = this->operator[](i);
            if (byte != 0xFF) {
                return i * 8 + __builtin_clz(~byte) - (sizeof(unsigned int) * 8 - 8);
            }
        }
        return GetByteSize() * 8;
    }

    virtual size_t CountTrailingOnes() const {
        for (size_t i = GetByteSize(); i > 0; --i) {
            uint8_t byte = this->operator[](i - 1);
            if (byte != 0xFF) {
                // Fixed: was checking ~byte != 0
                return (GetByteSize() - i) * 8 + __builtin_ctz(~byte);
            }
        }
        return GetByteSize() * 8;
    }
    
    // Pattern searching
    virtual std::optional<size_t> FindFirstSet() const {
        for (size_t i = GetByteSize(); i > 0; --i) {
            // Start from LSB
            uint8_t byte = this->operator[](i - 1);
            if (byte != 0) {
                return (GetByteSize() - i) * 8 + __builtin_ctz(byte);
            }
        }
        return GetByteSize() * 8 - CountTrailingOnes();
    }
    
    virtual std::optional<size_t> FindFirstClear() const {
        for (size_t i = GetByteSize(); i > 0; --i) {
            // Start from LSB
            uint8_t byte = this->operator[](i - 1);
            if (byte != 0xFF) {
                return (GetByteSize() - i) * 8 + __builtin_ctz(~byte);
            }
        }
        return GetByteSize() * 8 - CountTrailingZeros();
    }
    
    virtual std::optional<size_t> FindLastSet() const {
        for (size_t i = 0; i < GetByteSize(); ++i) {
            // Start from MSB
            uint8_t byte = this->operator[](i);
            if (byte != 0) {
                return i * 8 + (7 - (__builtin_clz(byte) - (sizeof(unsigned int) * 8 - 8)));
            }
        }
        return CountLeadingOnes() + 1;
    }
    
    virtual std::optional<size_t> FindLastClear() const {
        for (size_t i = 0; i < GetByteSize(); ++i) {
            // Start from MSB
            uint8_t byte = this->operator[](i);
            if (byte != 0xFF) {
                return i * 8 + (7 - (__builtin_clz(~byte) - (sizeof(unsigned int) * 8 - 8)));
            }
        }
        return CountLeadingOnes() + 1;
    }

    // Pattern testing
    virtual bool IsAllZeros() const {
        for (size_t i = 0; i < GetByteSize(); ++i) {
            if (this->operator[](i) != 0) {
                return false;
            }
        }
        return true;
    }
    
    virtual bool IsAllOnes() const {
        for (size_t i = 0; i < GetByteSize(); ++i) {
            if (this->operator[](i) != 0xFF) {
                return false;
            }
        }
        return true;
    }
    
    virtual bool IsPowerOfTwo() const {
        size_t popCount = PopCount();
        return popCount == 1;
    }
    
    virtual bool HasEvenParity() const {
        return !HasOddParity();
    }
    
    virtual bool HasOddParity() const {
        return PopCount() & 1;
    }

    // Range testing
    virtual bool TestBitRange(size_t start, size_t count, bool expectedValue) const {
        for (size_t i = 0; i < count; ++i) {
            size_t bitIndex = start + i;
            if (bitIndex >= GetByteSize() * 8) {
                return false; // Out of bounds
            }

            size_t byteIndex = bitIndex >> 3;
            size_t bitPosition = bitIndex & 7;
            bool actualValue = (this->operator[](byteIndex) & (1 << bitPosition)) != 0;

            if (actualValue != expectedValue) {
                return false;
            }
        }
        return true;
    }
};

#endif //IBITANALYZABLE_H
