//
// Created by Lumi on 25. 6. 16.
//

#ifndef IBITMANIPULABLE_H
#define IBITMANIPULABLE_H
#pragma once

class IBitManipulable : public IBitAnalyzable, IBitAccessible, IBitCopyable {
public:
    virtual ~IBitManipulable() = default;
    
    // Shifting and rotation
    
    virtual void ShiftLeft(size_t positions) = 0;
    
    virtual void ShiftRight(size_t positions) = 0;
    
    virtual void RotateLeft(size_t positions) = 0;
    
    virtual void RotateRight(size_t positions) = 0;

    // Bit reversal
    
    virtual void ReverseBits() = 0;
    
    virtual void ReverseBytes() = 0;

    // Bitwise operations with other objects
    
    virtual void BitwiseAnd(const IBitManipulable& other) = 0;
    
    virtual void BitwiseOr(const IBitManipulable& other) = 0;
    
    virtual void BitwiseXor(const IBitManipulable& other) = 0;
    
    virtual void BitwiseNot() = 0;
    
    virtual void Increment() {
        // Find a place where the trailing one ends,
        size_t trailingOnes = CountTrailingOnes();
        // if not any, just set the last bit,
        if (trailingOnes == 0) {
            SetBit(0);
        }
        // if it doesn't end, clear all the bits,
        else if (trailingOnes == GetBitSize()) {
            ClearAllBits();
        }
        // else, clear all the trailing ones
        else {
            ClearBitRange(0, trailingOnes);
            // and set the next bit
            SetBit(trailingOnes);
        }
    }
    
    virtual void Decrement() {
        // Find a place where the trailing zero ends,
        size_t trailingZeros = CountTrailingZeros();
        // if not any, just clear the last bit,
        if (trailingZeros == 0) {
            ClearBit(0);
        }
        // if it doesn't end, set all the bits,
        else if (trailingZeros == GetBitSize()) {
            SetAllBits();
        }
        // else, set all the trailing zeros
        else {
            SetBitRange(0, trailingZeros);
            // and clear the next bit
            ClearBit(trailingZeros);
        }
    }

    virtual void OffsetAdd(const IBitManipulable& other,
        size_t srcPosStart,
        size_t srcPosCount,
        size_t dstPosStart);

    virtual void OffsetSub(const IBitManipulable& other,
        size_t srcPosStart,
        size_t srcPosCount,
        size_t dstPosStart);
};

#endif //IBITMANIPULABLE_H
