//
// Created by Lumi on 25. 6. 16.
//

#ifndef IBITCOPYABLE_H
#define IBITCOPYABLE_H
#pragma once
#include <cstdint>
#include <functional>
#include <span>

class IBitCopyable {
public:
    virtual ~IBitCopyable() = default;
    
    // Internal copying (within the same object)
    virtual void CopyBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) = 0;
    
    virtual void MoveBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) = 0;
    
    // External copying (between objects)
    virtual void CopyBitsFrom(const IBitCopyable& source, 
                              size_t srcStart, size_t bitCount, size_t dstStart) = 0;
    
    virtual void CopyBitsTo(IBitCopyable& destination,
                            size_t srcStart, size_t bitCount, size_t dstStart) const = 0;
    
    // Range operations
    virtual void SetBitRange(size_t start, size_t count) = 0;
    
    virtual void ClearBitRange(size_t start, size_t count) = 0;
    
    virtual void FlipBitRange(size_t start, size_t count) = 0;
    
    // Validation
    virtual bool CanCopyBits(const IBitCopyable& source,
                             size_t srcStart, size_t bitCount, size_t dstStart) const = 0;
};
#endif //IBITCOPYABLE_H
