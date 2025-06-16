//
// Created by Lumi on 25. 6. 16.
//

#ifndef CPUSTORAGE_H
#define CPUSTORAGE_H

#include "../../include/interfaces/istorage.h"
#include <array>
#include <memory>
#include <algorithm>
#include <future>
#include <cstring>
#include <bit>
#include <sstream>
#include <iomanip>

template<size_t Bytes>
class CPUStorage : public IStorage {
    static_assert(Bytes > 0, "CPUStorage size must be greater than 0");

private:
    std::array<uint8_t, Bytes> data_{};
    static constexpr size_t totalBits = Bytes * 8;

public:
    CPUStorage() = default;
    CPUStorage(const CPUStorage& other) = default;
    CPUStorage(CPUStorage&& other) noexcept = default;
    CPUStorage& operator=(const CPUStorage& other) = default;
    CPUStorage& operator=(CPUStorage&& other) noexcept = default;

    // ===== IByteAccessible Implementation =====

    uint8_t& operator[](size_t index) override;

    const uint8_t& operator[](size_t index) const override;

    uint8_t* Data() override;

    const uint8_t* Data() const override;

    size_t GetByteSize() const override;

    void Fill(uint8_t value) override;

    void Clear() override;

    // ===== IBitAccessible Implementation =====

    bool GetBit(const size_t bitIndex) const override;

    void SetBit(const size_t bitIndex) override;

    void ClearBit(const size_t bitIndex) override;

    void FlipBit(const size_t bitIndex) override;

    size_t GetBitSize() const override;

    // ===== IBitAnalyzable Implementation =====

    size_t PopCount() const override;

    size_t CountLeadingZeros() const override;

    size_t CountTrailingZeros() const override;

    size_t CountLeadingOnes() const override;

    size_t CountTrailingOnes() const override;

    std::optional<size_t> FindFirstSet() const override;

    std::optional<size_t> FindFirstClear() const override;

    std::optional<size_t> FindLastSet() const override;

    std::optional<size_t> FindLastClear() const override;

    bool IsAllZeros() const override;

    bool IsAllOnes() const override;

    bool IsPowerOfTwo() const override;

    bool HasEvenParity() const override;

    bool HasOddParity() const override;

    bool TestBitRange(size_t start, size_t count, bool expectedValue) const override;

    // ===== IByteAnalyzable Implementation =====

    std::optional<size_t> FindByte(uint8_t value, size_t startPos = 0) const override;

    std::optional<size_t> FindBytePattern(std::span<const uint8_t> pattern, size_t startPos = 0) const override;

    int Compare(const IByteAnalyzable& other) const override;

    int Compare(std::span<const uint8_t> data) const override;

    bool Equal(const IByteAnalyzable& other) const override;

    bool Equal(std::span<const uint8_t> data) const override;

    uint32_t ComputeCRC32() const override;

    uint64_t ComputeHash() const override;

    // ===== IBitCopyable Implementation =====

    void CopyBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) override;

    void MoveBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) override;

    void CopyBitsFrom(const IBitCopyable& source, size_t srcStart, size_t bitCount, size_t dstStart) override;

    void CopyBitsTo(IBitCopyable& destination, size_t srcStart, size_t bitCount, size_t dstStart) const override;

    void SetBitRange(size_t start, size_t count) override;

    void ClearBitRange(size_t start, size_t count) override;

    void FlipBitRange(size_t start, size_t count) override;

    bool CanCopyBits(const IBitCopyable& source, size_t srcStart, size_t bitCount, size_t dstStart) const override;

    // ===== IByteCopyable Implementation =====

    void CopyBytesInternal(size_t srcStart, size_t byteCount, size_t dstStart) override;

    void MoveBytesInternal(size_t srcStart, size_t byteCount, size_t dstStart) override;

    void CopyBytesFrom(const IByteCopyable& source, size_t srcStart, size_t byteCount, size_t dstStart) override;

    void CopyBytesTo(IByteCopyable& destination, size_t srcStart, size_t byteCount, size_t dstStart) const override;

    void CopyFromBytes(const uint8_t* data, size_t dataSize, size_t srcStart, size_t dstStart,
        size_t copyCount) override;

    void CopyToBytes(uint8_t* data, size_t dataSize, size_t srcStart, size_t dstStart,
        size_t copyCount) const override;

    void CopyFromSpan(std::span<const uint8_t> source, size_t dstStart = 0) override;

    void CopyToSpan(std::span<uint8_t> destination, size_t srcStart = 0) const override;

    bool CanCopyBytes(const IByteCopyable& source, size_t srcStart, size_t byteCount, size_t dstStart) const override;

    // ===== IBitManipulable Implementation =====

    void ShiftLeft(size_t positions) override;

    void ShiftRight(size_t positions) override;

    void RotateLeft(size_t positions) override;

    void RotateRight(size_t positions) override;

    void ReverseBits() override;

    void ReverseBytes() override;

    void BitwiseAnd(const IBitManipulable& other) override;

    void BitwiseOr(const IBitManipulable& other) override;

    void BitwiseXor(const IBitManipulable& other) override;

    void BitwiseNot() override;

    // ===== IByteManipulable Implementation =====

    void SwapBytes(size_t index1, size_t index2) override;

    void ReverseByteOrder() override;

    void ShiftBytesLeft(size_t positions) override;

    void ShiftBytesRight(size_t positions) override;

    void ShiftBytesLeft(size_t positions, uint8_t fillValue) override;

    void ShiftBytesRight(size_t positions, uint8_t fillValue) override;

    void ToLittleEndian() override;

    void ToBigEndian() override;

    void ToNativeEndian() override;

    void BytewiseAnd(const IByteManipulable& other) override;

    void BytewiseOr(const IByteManipulable& other) override;

    void BytewiseXor(const IByteManipulable& other) override;

    void BytewiseNot() override;

    // ===== ESSENTIAL FACTORY METHODS (from IStorage) =====

    std::unique_ptr<IStorage> Clone() const override {
        return std::make_unique<CPUStorage<Bytes> >(*this);
    }

    std::unique_ptr<IStorage> CreateSimilar(size_t byteSize) const override;

    // ===== Additional Helper Methods =====

    // Direct access to underlying data for performance
    const std::array<uint8_t, Bytes>& GetData() const;

    std::array<uint8_t, Bytes>& GetData();

    // Efficient bulk operations
    void BitwiseAnd(const CPUStorage<Bytes>& other);

    void BitwiseOr(const CPUStorage<Bytes>& other);

    void BitwiseXor(const CPUStorage<Bytes>& other);

    // Comparison operators for convenience
    bool operator==(const CPUStorage<Bytes>& other) const;

    bool operator!=(const CPUStorage<Bytes>& other) const;

    // Stream output for debugging
    friend std::ostream& operator<<(std::ostream& os, const CPUStorage<Bytes>& storage);
};

// ===== Factory Function =====

template<size_t Bytes>
std::unique_ptr<IStorage> CreateCPUStorage();

// ===== Memory Place for ArbitrarySignedInt =====

struct CPUMemoryPlace {
    template<size_t Bytes>
    using storage_type = CPUStorage<Bytes>;

    template<size_t Bytes>
    static std::unique_ptr<IStorage> create() {
        return std::make_unique<CPUStorage<Bytes> >();
    }
};

#endif //CPUSTORAGE_H
