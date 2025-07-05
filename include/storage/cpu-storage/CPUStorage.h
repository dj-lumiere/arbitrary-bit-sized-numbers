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

    CPUStorage() {
        data_.fill(0);
    }

    // Implementations for Storage concept
    std::unique_ptr<CPUStorage<size>> Clone() const {
        return std::make_unique<CPUStorage<size>>(*this);
    }

    // BitAccessible implementations
    bool GetBit(const size_t bitIndex) const {
        if (bitIndex >= size * 8)
            throw std::out_of_range("Bit index out of bounds");
        return (data_[bitIndex / 8] >> (bitIndex % 8)) & 1;
    }
    void SetBit(const size_t bitIndex) {
        if (bitIndex >= size * 8)
            throw std::out_of_range("Bit index out of bounds");
        data_[bitIndex / 8] |= (1 << (bitIndex % 8));
    }
    void SetBit(const size_t bitIndex, const bool value) {
        if (value)
            SetBit(bitIndex);
        else
            ClearBit(bitIndex);
    }
    void ClearBit(const size_t bitIndex) {
        if (bitIndex >= size * 8)
            throw std::out_of_range("Bit index out of bounds");
        data_[bitIndex / 8] &= ~(1 << (bitIndex % 8));
    }
    void FlipBit(const size_t bitIndex) {
        if (bitIndex >= size * 8)
            throw std::out_of_range("Bit index out of bounds");
        data_[bitIndex / 8] ^= (1 << (bitIndex % 8));
    }
    void SetAllBits() {
        data_.fill(0xFF);
    }
    void ClearAllBits() {
        data_.fill(0x00);
    }
    void FlipAllBits() {
        for (size_t i = 0; i < size; ++i) {
            data_[i] = ~data_[i];
        }
    }

    constexpr size_t GetBitSize() const {
        return size * 8;
    }

    // BitAnalyzable implementations
    size_t PopCount() const {
        size_t count = 0;
        for (size_t i = 0; i < size; ++i) {
            count += std::popcount(data_[i]);
        }
        return count;
    }
    size_t CountLeadingZeros() const {
        size_t count = 0;
        for (size_t i = size - 1; i < size; --i) {
            if (data_[i] == 0) {
                count += 8;
            } else {
                count += std::countl_zero(data_[i]);
                break;
            }
        }
        return count;
    }
    size_t CountTrailingZeros() const {
        size_t count = 0;
        for (size_t i = 0; i < size; ++i) {
            if (data_[i] == 0) {
                count += 8;
            } else {
                count += std::countr_zero(data_[i]);
                break;
            }
        }
        return count;
    }
    size_t CountLeadingOnes() const {
        size_t count = 0;
        for (size_t i = size - 1; i < size; --i) {
            if (data_[i] == 0xFF) {
                count += 8;
            } else {
                count += std::countl_one(data_[i]);
                break;
            }
        }
        return count;
    }
    size_t CountTrailingOnes() const {
        size_t count = 0;
        for (size_t i = 0; i < size; ++i) {
            if (data_[i] == 0xFF) {
                count += 8;
            } else {
                count += std::countr_one(data_[i]);
                break;
            }
        }
        return count;
    }
    std::optional<size_t> FindFirstSet() const {
        for (size_t i = 0; i < size; ++i) {
            if (data_[i] != 0) {
                return i * 8 + std::countr_zero(data_[i]);
            }
        }
        return std::nullopt;
    }
    std::optional<size_t> FindFirstClear() const {
        for (size_t i = 0; i < size; ++i) {
            if (data_[i] != 0xFF) {
                return i * 8 + std::countr_one(data_[i]);
            }
        }
        return std::nullopt;
    }
    std::optional<size_t> FindLastSet() const {
        for (size_t i = size - 1; i < size; --i) {
            if (data_[i] != 0) {
                return i * 8 + 7 - std::countl_zero(data_[i]);
            }
        }
        return std::nullopt;
    }
    std::optional<size_t> FindLastClear() const {
        for (size_t i = size - 1; i < size; --i) {
            if (data_[i] != 0xFF) {
                return i * 8 + 7 - std::countl_one(data_[i]);
            }
        }
        return std::nullopt;
    }
    bool IsAllZeros() const {
        return std::all_of(data_.begin(), data_.end(), [](uint8_t b) { return b == 0; });
    }
    bool IsAllOnes() const {
        return std::all_of(data_.begin(), data_.end(), [](uint8_t b) { return b == 0xFF; });
    }
    bool IsPowerOfTwo() const {
        return PopCount() == 1;
    }
    bool HasEvenParity() const {
        return PopCount() % 2 == 0;
    }
    bool HasOddParity() const {
        return PopCount() % 2 != 0;
    }
    bool TestBitRange(size_t start, size_t count, bool expectedValue) const {
        for (size_t i = 0; i < count; ++i) {
            if (GetBit(start + i) != expectedValue) {
                return false;
            }
        }
        return true;
    }

    // BitCopyable implementations
    void CopyBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) {
        for (size_t i = 0; i < bitCount; ++i) {
            SetBit(dstStart + i, GetBit(srcStart + i));
        }
    }
    void MoveBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) {
        if (dstStart > srcStart) {
            for (size_t i = bitCount; i > 0; --i) {
                SetBit(dstStart + i - 1, GetBit(srcStart + i - 1));
            }
        } else {
            for (size_t i = 0; i < bitCount; ++i) {
                SetBit(dstStart + i, GetBit(srcStart + i));
            }
        }
    }
    void CopyBitsFrom(const CPUStorage& source, size_t srcStart, size_t bitCount, size_t dstStart) {
        for (size_t i = 0; i < bitCount; ++i) {
            SetBit(dstStart + i, source.GetBit(srcStart + i));
        }
    }
    void CopyBitsTo(CPUStorage& destination, size_t srcStart, size_t bitCount, size_t dstStart) const {
        for (size_t i = 0; i < bitCount; ++i) {
            destination.SetBit(dstStart + i, GetBit(srcStart + i));
        }
    }
    void SetBitRange(size_t start, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            SetBit(start + i);
        }
    }
    void ClearBitRange(size_t start, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            ClearBit(start + i);
        }
    }
    void FlipBitRange(size_t start, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            FlipBit(start + i);
        }
    }
    bool CanCopyBits(const CPUStorage& source, size_t srcStart, size_t bitCount, size_t dstStart) const {
        return srcStart + bitCount <= source.GetByteSize() * 8 && dstStart + bitCount <= GetByteSize() * 8;
    }

    // BitManipulable implementations
    void ShiftLeft(size_t positions) {
        if (positions == 0) {
            return;
        }

        size_t byteOffset = positions >> 3;
        size_t bitOffset = positions & 7;
        ShiftBytesLeft(byteOffset);
        if (bitOffset == 0) {
            return;
        }
        // Process from HIGH to LOW bytes (right to left)
        for (size_t i = size - 1; i > 0; --i) {
            data_[i] <<= bitOffset;
            data_[i] |= data_[i - 1] >> (8 - bitOffset); // Get carry from lower byte
        }
        // Handle the lowest byte (no carry from below)
        data_[0] <<= bitOffset;
    }
    void ShiftRight(size_t positions) {
        if (positions == 0) {
            return;
        }

        size_t byteOffset = positions >> 3;
        size_t bitOffset = positions & 7;
        ShiftBytesRight(byteOffset);
        if (bitOffset == 0) {
            return;
        }
        for (size_t i = 0; i < size - 1; ++i) {
            data_[i] >>= bitOffset;
            data_[i] |= data_[i + 1] << (8 - bitOffset);
        }
        // Handle the highest byte (no carry from above)
        data_[size - 1] >>= bitOffset;
    }
    void RotateLeft(size_t positions) {
        positions %= totalBits; // Handle rotations larger than size
        if (positions == 0)
            return;

        // Save the bits that will wrap around
        std::vector<bool> wrapBits(positions);
        for (size_t i = 0; i < positions; ++i) {
            wrapBits[i] = GetBit(totalBits - positions + i);
        }

        // Shift left
        ShiftLeft(positions);

        // Set the wrapped bits
        for (size_t i = 0; i < positions; ++i) {
            if (wrapBits[i]) {
                SetBit(i);
            }
            else {
                ClearBit(i);
            }
        }
    }
    void RotateRight(size_t positions) {
        positions %= totalBits;
        if (positions == 0)
            return;

        // Save the bits that will wrap around
        std::vector<bool> wrapBits(positions);
        for (size_t i = 0; i < positions; ++i) {
            wrapBits[i] = GetBit(i);
        }

        // Shift right
        ShiftRight(positions);

        // Set the wrapped bits
        for (size_t i = 0; i < positions; ++i) {
            if (wrapBits[i]) {
                SetBit(totalBits - positions + i);
            }
            else {
                ClearBit(totalBits - positions + i);
            }
        }
    }
    void ReverseBits() {
        for (size_t i = 0; i < totalBits / 2; ++i) {
            bool leftBit = GetBit(i);
            bool rightBit = GetBit(totalBits - 1 - i);

            if (leftBit) {
                SetBit(totalBits - 1 - i);
            }
            else {
                ClearBit(totalBits - 1 - i);
            }

            if (rightBit) {
                SetBit(i);
            }
            else {
                ClearBit(i);
            }
        }
    }
    void ReverseBytes() {
        std::reverse(data_.begin(), data_.end());
    }
    void BitwiseAnd(const CPUStorage& other) {
        for (size_t i = 0; i < size; ++i) {
            data_[i] &= other.data_[i];
        }
    }
    void BitwiseOr(const CPUStorage& other) {
        for (size_t i = 0; i < size; ++i) {
            data_[i] |= other.data_[i];
        }
    }
    void BitwiseXor(const CPUStorage& other) {
        for (size_t i = 0; i < size; ++i) {
            data_[i] ^= other.data_[i];
        }
    }
    void BitwiseNot() {
        for (size_t i = 0; i < size; ++i) {
            data_[i] = ~data_[i];
        }
    }
    void Increment() {
        for (size_t i = 0; i < size; ++i) {
            if (++data_[i] != 0) {
                break;
            }
        }
    }
    void Decrement() {
        for (size_t i = 0; i < size; ++i) {
            if (--data_[i] != 0xFF) {
                break;
            }
        }
    }
    void OffsetAdd(size_t offset, size_t bitWidth, size_t value) {
        if (offset + bitWidth > totalBits) {
            throw std::out_of_range("Bit range out of bounds in OffsetAdd");
        }

        bool carry = false;
        for (size_t i = 0; i < bitWidth; ++i) {
            bool current_bit = GetBit(offset + i);
            bool value_bit = (value >> i) & 1;

            bool sum_bit = current_bit ^ value_bit ^ carry;
            carry = (current_bit && value_bit) || (current_bit && carry) || (value_bit && carry);

            SetBit(offset + i, sum_bit);
        }
    }
    void OffsetSub(size_t offset, size_t bitWidth, size_t value) {
        if (offset + bitWidth > totalBits) {
            throw std::out_of_range("Bit range out of bounds in OffsetSub");
        }

        bool borrow = false;
        for (size_t i = 0; i < bitWidth; ++i) {
            bool current_bit = GetBit(offset + i);
            bool value_bit = (value >> i) & 1;

            bool diff_bit = current_bit ^ value_bit ^ borrow;
            borrow = (!current_bit && value_bit) || (!current_bit && borrow) || (value_bit && borrow);

            SetBit(offset + i, diff_bit);
        }
    }
    template<size_t OtherSize>
    void OffsetAdd(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart) {
        if (srcStart + srcWidth > ct.totalBits) {
            throw std::out_of_range("Source bit range out of bounds in OffsetAdd (CPUStorage overload)");
        }

        bool carry = false;
        for (size_t i = 0; i < srcWidth; ++i) {
            if (dstStart + i >= totalBits) {
                // Discard leftover bits
                break;
            }
            bool current_dst_bit = GetBit(dstStart + i);
            bool src_bit = ct.GetBit(srcStart + i);

            bool sum_bit = current_dst_bit ^ src_bit ^ carry;
            carry = (current_dst_bit && src_bit) || (current_dst_bit && carry) || (src_bit && carry);

            SetBit(dstStart + i, sum_bit);
        }
    }
    template<size_t OtherSize>
    void OffsetSub(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart) {
        if (srcStart + srcWidth > ct.totalBits) {
            throw std::out_of_range("Source bit range out of bounds in OffsetSub (CPUStorage overload)");
        }

        bool borrow = false;
        for (size_t i = 0; i < srcWidth; ++i) {
            if (dstStart + i >= totalBits) {
                // Discard leftover bits
                break;
            }
            bool current_dst_bit = GetBit(dstStart + i);
            bool src_bit = ct.GetBit(srcStart + i);

            bool diff_bit = current_dst_bit ^ src_bit ^ borrow;
            borrow = (!current_dst_bit && src_bit) || (!current_dst_bit && borrow) || (src_bit && borrow);

            SetBit(dstStart + i, diff_bit);
        }
    }

    // ByteAccessible implementations
    uint8_t& operator[](size_t index) {
        if (index >= size)
            throw std::out_of_range("Index out of bounds");
        return data_[index];
    }
    const uint8_t& operator[](size_t index) const {
        if (index >= size)
            throw std::out_of_range("Index out of bounds");
        return data_[index];
    }
    uint8_t* Data() {
        return data_.data();
    }
    const uint8_t* Data() const {
        return data_.data();
    }
    constexpr size_t GetByteSize() const {
        return size;
    }
    void Fill(uint8_t value) {
        data_.fill(value);
    }
    void Clear() {
        data_.fill(0);
    }

    // ByteAnalyzable implementations
    std::optional<size_t> FindByte(uint8_t value, size_t startPos = 0) const {
        auto it = std::find(data_.begin() + startPos, data_.end(), value);
        if (it != data_.end()) {
            return std::distance(data_.begin(), it);
        }
        return std::nullopt;
    }
    std::optional<size_t> FindBytePattern(std::span<const uint8_t> pattern, size_t startPos = 0) const {
        auto it = std::search(data_.begin() + startPos, data_.end(), pattern.begin(), pattern.end());
        if (it != data_.end()) {
            return std::distance(data_.begin(), it);
        }
        return std::nullopt;
    }
    int Compare(const CPUStorage& other) const {
        return std::memcmp(data_.data(), other.data_.data(), size);
    }
    int Compare(std::span<const uint8_t> data) const {
        return std::memcmp(data_.data(), data.data(), std::min(size, data.size()));
    }
    bool Equal(const CPUStorage& other) const {
        return data_ == other.data_;
    }
    bool Equal(std::span<const uint8_t> data) const {
        return std::equal(data_.begin(), data_.end(), data.begin(), data.end());
    }
    uint32_t ComputeCRC32() const {
        // Not implemented
        return 0;
    }
    uint64_t ComputeHash() const {
        // Not implemented
        return 0;
    }

    // ByteCopyable implementations - Fixed method names
    void CopyBytesInternal(size_t srcStart, size_t count, size_t dst) {
        std::copy(data_.begin() + srcStart, data_.begin() + srcStart + count, data_.begin() + dst);
    }
    void MoveBytesInternal(size_t srcStart, size_t count, size_t dst) {
        std::move(data_.begin() + srcStart, data_.begin() + srcStart + count, data_.begin() + dst);
    }
    void CopyBytesFrom(const CPUStorage& source, size_t srcStart, size_t count, size_t dst) {
        std::copy(source.data_.begin() + srcStart, source.data_.begin() + srcStart + count, data_.begin() + dst);
    }
    void CopyBytesTo(CPUStorage& destination, size_t srcStart, size_t count, size_t dst) const {
        std::copy(data_.begin() + srcStart, data_.begin() + srcStart + count, destination.data_.begin() + dst);
    }
    void CopyFromBytes(const uint8_t* src, size_t srcByteSize, size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) {
        std::copy(src + srcOffsetBytes, src + srcOffsetBytes + countBytes, data_.begin() + dstOffsetBytes);
    }
    void CopyToBytes(uint8_t* dst, size_t dstByteSize, size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) const {
        std::copy(data_.begin() + srcOffsetBytes, data_.begin() + srcOffsetBytes + countBytes, dst + dstOffsetBytes);
    }
    void CopyFromSpan(std::span<const uint8_t> src_span, size_t dst) {
        std::copy(src_span.begin(), src_span.end(), data_.begin() + dst);
    }
    void CopyToSpan(std::span<uint8_t> dst_span, size_t start) const {
        std::copy(data_.begin() + start, data_.begin() + start + dst_span.size(), dst_span.begin());
    }
    bool CanCopyBytes(const CPUStorage& source, size_t srcStart, size_t count, size_t dst) const {
        return srcStart + count <= source.GetByteSize() && dst + count <= GetByteSize();
    }
    void MoveBytes(size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) {
        MoveBytesInternal(srcOffsetBytes, countBytes, dstOffsetBytes);
    }
    bool CanCopyBytes(size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) const {
        return srcOffsetBytes + countBytes <= size && dstOffsetBytes + countBytes <= size;
    }

    // ByteManipulable implementations
    void SwapBytes(size_t index1, size_t index2) {
        std::swap(data_[index1], data_[index2]);
    }
    void ReverseByteOrder() {
        std::reverse(data_.begin(), data_.end());
    }
    void ShiftBytesLeft(size_t positions) {
        if (positions >= size) {
            data_.fill(0);
            return;
        }
        std::move(data_.begin() + positions, data_.end(), data_.begin());
        std::fill(data_.end() - positions, data_.end(), 0);
    }
    void ShiftBytesRight(size_t positions) {
        if (positions >= size) {
            data_.fill(0);
            return;
        }
        std::move_backward(data_.begin(), data_.end() - positions, data_.end());
        std::fill(data_.begin(), data_.begin() + positions, 0);
    }
    void ShiftBytesLeft(size_t positions, uint8_t fillValue) {
        if (positions >= size) {
            data_.fill(fillValue);
            return;
        }
        std::move(data_.begin() + positions, data_.end(), data_.begin());
        std::fill(data_.end() - positions, data_.end(), fillValue);
    }
    void ShiftBytesRight(size_t positions, uint8_t fillValue) {
        if (positions >= size) {
            data_.fill(fillValue);
            return;
        }
        std::move_backward(data_.begin(), data_.end() - positions, data_.end());
        std::fill(data_.begin(), data_.begin() + positions, fillValue);
    }
    void ToLittleEndian() {
        // Already in little endian on most systems, but implement for completeness
    }
    void ToBigEndian() {
        ReverseByteOrder();
    }
    void ToNativeEndian() {
        // Assume native is little endian
    }
    void BytewiseAnd(const CPUStorage& other) {
        for (size_t i = 0; i < size; ++i) {
            data_[i] &= other.data_[i];
        }
    }
    void BytewiseOr(const CPUStorage& other) {
        for (size_t i = 0; i < size; ++i) {
            data_[i] |= other.data_[i];
        }
    }
    void BytewiseXor(const CPUStorage& other) {
        for (size_t i = 0; i < size; ++i) {
            data_[i] ^= other.data_[i];
        }
    }
    void BytewiseNot() {
        for (size_t i = 0; i < size; ++i) {
            data_[i] = ~data_[i];
        }
    }
};

// CPUStorageProvider remains the same, as it's already a factory for CPUStorage
class CPUStorageProvider {
public:
    
    // Add this type alias to help with storage type deduction
    template<size_t size>
    using StorageType = CPUStorage<size>;
    
    template<size_t size>
    static CPUStorage<size> create() {
        return CPUStorage<size>();
    }
};

#endif //CPUSTORAGE_H
