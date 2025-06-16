//
// Created by Lumi on 25. 6. 16.
//

#ifndef IBYTECOPYABLE_H
#define IBYTECOPYABLE_H
#include <cstdint>
#include <span>

class IByteCopyable {
public:
    virtual ~IByteCopyable() = default;

    // Internal copying (within same object)
    virtual void CopyBytesInternal(size_t srcStart, size_t byteCount, size_t dstStart) = 0;
    virtual void MoveBytesInternal(size_t srcStart, size_t byteCount, size_t dstStart) = 0;

    // External copying (between objects)
    virtual void CopyBytesFrom(const IByteCopyable& source,
        size_t srcStart, size_t byteCount, size_t dstStart) = 0;
    virtual void CopyBytesTo(IByteCopyable& destination,
        size_t srcStart, size_t byteCount, size_t dstStart) const = 0;

    // Raw data copying
    virtual void CopyFromBytes(const uint8_t* data, size_t dataSize,
        size_t srcStart, size_t dstStart, size_t copyCount) = 0;
    virtual void CopyToBytes(uint8_t* data, size_t dataSize,
        size_t srcStart, size_t dstStart, size_t copyCount) const = 0;

    // Span operations
    virtual void CopyFromSpan(std::span<const uint8_t> source, size_t dstStart = 0) = 0;
    virtual void CopyToSpan(std::span<uint8_t> destination, size_t srcStart = 0) const = 0;

    // Validation
    virtual bool CanCopyBytes(const IByteCopyable& source,
        size_t srcStart, size_t byteCount, size_t dstStart) const = 0;
};

#endif //IBYTECOPYABLE_H
