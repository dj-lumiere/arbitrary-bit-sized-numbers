#ifndef CPUSTORAGE_H
#define CPUSTORAGE_H

#include <array>
#include <memory>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <optional>
#include <span>
#include <numeric>
#include <cstring>

// Forward declaration of CPUStorageProvider
class CPUStorageProvider;

template<size_t size>
class CPUStorage {
public:
    std::array<uint8_t, size> data_;
    static constexpr size_t totalBits = size << 3;

    CPUStorage();

    // Implementations for Storage concept
    std::unique_ptr<CPUStorage<size> > Clone() const;

    // BitAccessible implementations
    bool GetBit(const size_t bitIndex) const;
    void SetBit(const size_t bitIndex);
    void SetBit(const size_t bitIndex, const bool value);
    void ClearBit(const size_t bitIndex);
    void FlipBit(const size_t bitIndex);
    void SetAllBits();
    void ClearAllBits();
    void FlipAllBits();
    constexpr size_t GetBitSize() const;

    // BitAnalyzable implementations
    size_t PopCount() const;
    size_t CountLeadingZeros() const;
    size_t CountTrailingZeros() const;
    size_t CountLeadingOnes() const;
    size_t CountTrailingOnes() const;
    std::optional<size_t> FindFirstSet() const;
    std::optional<size_t> FindFirstClear() const;
    std::optional<size_t> FindLastSet() const;
    std::optional<size_t> FindLastClear() const;
    bool IsAllZeros() const;
    bool IsAllOnes() const;
    bool IsPowerOfTwo() const;
    bool HasEvenParity() const;
    bool HasOddParity() const;
    bool TestBitRange(size_t start, size_t count, bool expectedValue) const;

    // BitCopyable implementations
    void CopyBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart);
    void MoveBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart);
    template<size_t OtherSize>
    void CopyBitsFrom(const CPUStorage<OtherSize>& source, size_t srcStart, size_t bitCount, size_t dstStart);
    template<size_t OtherSize>
    void CopyBitsTo(CPUStorage<OtherSize>& destination, size_t srcStart, size_t bitCount, size_t dstStart) const;
    void SetBitRange(size_t start, size_t count);
    void ClearBitRange(size_t start, size_t count);
    void FlipBitRange(size_t start, size_t count);
    template<size_t OtherSize>
    bool CanCopyBits(const CPUStorage<OtherSize>& source, size_t srcStart, size_t bitCount, size_t dstStart) const;

    // BitManipulable implementations
    void ShiftLeft(size_t positions);
    void ShiftRight(size_t positions);
    void RotateLeft(size_t positions);
    void RotateRight(size_t positions);
    void ReverseBits();
    void ReverseBytes();
    void BitwiseAnd(const CPUStorage& other);
    void BitwiseOr(const CPUStorage& other);
    void BitwiseXor(const CPUStorage& other);
    void BitwiseNot();
    void Increment();
    void Decrement();
    void OffsetAdd(size_t offset, size_t bitWidth, size_t value);
    void OffsetSub(size_t offset, size_t bitWidth, size_t value);
    template<size_t OtherSize>
    void OffsetAdd(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart);
    template<size_t OtherSize>
    void OffsetSub(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart);
    std::pair<CPUStorage<size>, bool> OffsetAddWithCarry(size_t offset, size_t bitWidth, size_t value, bool initialCarry);
    std::pair<CPUStorage<size>, bool> OffsetSubWithBorrow(size_t offset, size_t bitWidth, size_t value, bool initialBorrow);
    template<size_t OtherSize>
    std::pair<CPUStorage<size>, bool> OffsetAddWithCarry(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart, bool initialCarry);
    template<size_t OtherSize>
    std::pair<CPUStorage<size>, bool> OffsetSubWithBorrow(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart, bool initialBorrow);

    // ByteAccessible implementations
    uint8_t& operator[](size_t index);
    const uint8_t& operator[](size_t index) const;
    uint8_t* Data();
    const uint8_t* Data() const;
    constexpr size_t GetByteSize() const;
    void Fill(uint8_t value);
    void Clear();

    // ByteAnalyzable implementations
    std::optional<size_t> FindByte(uint8_t value, size_t startPos = 0) const;
    std::optional<size_t> FindBytePattern(std::span<const uint8_t> pattern, size_t startPos = 0) const;
    int Compare(const CPUStorage& other) const;
    int Compare(std::span<const uint8_t> data) const;
    bool Equal(const CPUStorage& other) const;
    bool Equal(std::span<const uint8_t> data) const;
    uint32_t ComputeCRC32() const;
    uint64_t ComputeHash() const;

    // ByteCopyable implementations
    void CopyBytesInternal(size_t srcStart, size_t count, size_t dst);
    void MoveBytesInternal(size_t srcStart, size_t count, size_t dst);
    template<size_t OtherSize>
    void CopyBytesFrom(const CPUStorage<OtherSize>& source, size_t srcStart, size_t count, size_t dst);
    template<size_t OtherSize>
    void CopyBytesTo(CPUStorage<OtherSize>& destination, size_t srcStart, size_t count, size_t dst) const;
    void CopyFromBytes(const uint8_t* src, size_t srcByteSize, size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes);
    void CopyToBytes(uint8_t* dst, size_t dstByteSize, size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) const;
    void CopyFromSpan(std::span<const uint8_t> src_span, size_t dst);
    void CopyToSpan(std::span<uint8_t> dst_span, size_t start) const;
    template<size_t OtherSize>
    bool CanCopyBytes(const CPUStorage<OtherSize>& source, size_t srcStart, size_t count, size_t dst) const;
    void MoveBytes(size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes);
    bool CanCopyBytes(size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) const;

    // ByteManipulable implementations
    void SwapBytes(size_t index1, size_t index2);
    void ReverseByteOrder();
    void ShiftBytesLeft(size_t positions);
    void ShiftBytesRight(size_t positions);
    void ShiftBytesLeft(size_t positions, uint8_t fillValue);
    void ShiftBytesRight(size_t positions, uint8_t fillValue);
    void ToLittleEndian();
    void ToBigEndian();
    void ToNativeEndian();
    void BytewiseAnd(const CPUStorage& other);
    void BytewiseOr(const CPUStorage& other);
    void BytewiseXor(const CPUStorage& other);
    void BytewiseNot();
};

template<size_t size>
CPUStorage<size>::CPUStorage() {
    data_.fill(0);
}

template<size_t size>
std::unique_ptr<CPUStorage<size> > CPUStorage<size>::Clone() const {
    return std::make_unique<CPUStorage<size> >(*this);
}

#include <storage/cpu-storage/impl/CPUStorageImpl.h>

class CPUStorageProvider {
public:
    template<size_t size>
    using StorageType = CPUStorage<size>;

    template<size_t size>
    static CPUStorage<size> create() {
        return CPUStorage<size>();
    }
};

#endif //CPUSTORAGE_H
