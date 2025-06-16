//
// Created by Lumi on 25. 6. 16.
//
#include "storage/CPUStorage.h"

// ===== IByteAccessible Implementation =====

template<size_t Bytes>
uint8_t& CPUStorage<Bytes>::operator[](size_t index) {
    if (index >= Bytes) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<size_t Bytes>
const uint8_t& CPUStorage<Bytes>::operator[](size_t index) const {
    if (index >= Bytes) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<size_t Bytes>
uint8_t* CPUStorage<Bytes>::Data() {
    return data_.data();
}

template<size_t Bytes>
const uint8_t* CPUStorage<Bytes>::Data() const {
    return data_.data();
}

template<size_t Bytes>
size_t CPUStorage<Bytes>::GetByteSize() const {
    return Bytes;
}

template<size_t Bytes>
void CPUStorage<Bytes>::Fill(uint8_t value) {
    data_.fill(value);
}

template<size_t Bytes>
void CPUStorage<Bytes>::Clear() {
    data_.fill(0);
}

// ===== IBitAccessible Implementation =====

template<size_t Bytes>
bool CPUStorage<Bytes>::GetBit(const size_t bitIndex) const {
    if (bitIndex >= totalBits) {
        return false;
    }
    return data_[bitIndex >> 3] & (1 << (bitIndex & 7));
}

template<size_t Bytes>
void CPUStorage<Bytes>::SetBit(const size_t bitIndex) {
    if (bitIndex < totalBits) {
        data_[bitIndex >> 3] |= (1 << (bitIndex & 7));
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::ClearBit(const size_t bitIndex) {
    if (bitIndex < totalBits) {
        data_[bitIndex >> 3] &= ~(1 << (bitIndex & 7));
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::FlipBit(const size_t bitIndex) {
    if (bitIndex < totalBits) {
        data_[bitIndex >> 3] ^= (1 << (bitIndex & 7));
    }
}

template<size_t Bytes>
size_t CPUStorage<Bytes>::GetBitSize() const {
    return totalBits;
}

// ===== IBitAnalyzable Implementation =====

template<size_t Bytes>
size_t CPUStorage<Bytes>::PopCount() const {
    size_t count = 0;
    for (const auto& byte : data_) {
        count += std::popcount(static_cast<unsigned char>(byte));
    }
    return count;
}

template<size_t Bytes>
size_t CPUStorage<Bytes>::CountLeadingZeros() const {
    for (size_t i = 0; i < Bytes; ++i) {
        uint8_t byte = data_[i];
        if (byte != 0) {
            return i * 8 + std::countl_zero(static_cast<unsigned char>(byte));
        }
    }
    return totalBits;
}

template<size_t Bytes>
size_t CPUStorage<Bytes>::CountTrailingZeros() const {
    for (size_t i = Bytes; i > 0; --i) {
        uint8_t byte = data_[i - 1];
        if (byte != 0) {
            return (Bytes - i) * 8 + std::countr_zero(static_cast<unsigned char>(byte));
        }
    }
    return totalBits;
}

template<size_t Bytes>
size_t CPUStorage<Bytes>::CountLeadingOnes() const {
    for (size_t i = 0; i < Bytes; ++i) {
        uint8_t byte = data_[i];
        if (byte != 0xFF) {
            return i * 8 + std::countl_one(static_cast<unsigned char>(byte));
        }
    }
    return totalBits;
}

template<size_t Bytes>
size_t CPUStorage<Bytes>::CountTrailingOnes() const {
    for (size_t i = Bytes; i > 0; --i) {
        uint8_t byte = data_[i - 1];
        if (byte != 0xFF) {
            return (Bytes - i) * 8 + std::countr_one(static_cast<unsigned char>(byte));
        }
    }
    return totalBits;
}

template<size_t Bytes>
std::optional<size_t> CPUStorage<Bytes>::FindFirstSet() const {
    for (size_t i = Bytes; i > 0; --i) {
        uint8_t byte = data_[i - 1];
        if (byte != 0) {
            return (Bytes - i) * 8 + std::countr_zero(static_cast<unsigned char>(byte));
        }
    }
    return std::nullopt;
}

template<size_t Bytes>
std::optional<size_t> CPUStorage<Bytes>::FindFirstClear() const {
    for (size_t i = Bytes; i > 0; --i) {
        uint8_t byte = data_[i - 1];
        if (byte != 0xFF) {
            return (Bytes - i) * 8 + std::countr_zero(static_cast<unsigned char>(~byte));
        }
    }
    return std::nullopt;
}

template<size_t Bytes>
std::optional<size_t> CPUStorage<Bytes>::FindLastSet() const {
    for (size_t i = 0; i < Bytes; ++i) {
        uint8_t byte = data_[i];
        if (byte != 0) {
            return i * 8 + (7 - std::countl_zero(static_cast<unsigned char>(byte)));
        }
    }
    return std::nullopt;
}

template<size_t Bytes>
std::optional<size_t> CPUStorage<Bytes>::FindLastClear() const {
    for (size_t i = 0; i < Bytes; ++i) {
        uint8_t byte = data_[i];
        if (byte != 0xFF) {
            return i * 8 + (7 - std::countl_zero(static_cast<unsigned char>(~byte)));
        }
    }
    return std::nullopt;
}

template<size_t Bytes>
bool CPUStorage<Bytes>::IsAllZeros() const {
    return std::all_of(data_.begin(), data_.end(), [](uint8_t b) {
        return b == 0;
    });
}

template<size_t Bytes>
bool CPUStorage<Bytes>::IsAllOnes() const {
    return std::all_of(data_.begin(), data_.end(), [](uint8_t b) {
        return b == 0xFF;
    });
}

template<size_t Bytes>
bool CPUStorage<Bytes>::IsPowerOfTwo() const {
    const size_t popCount = PopCount();
    return popCount == 1;
}

template<size_t Bytes>
bool CPUStorage<Bytes>::HasEvenParity() const {
    return (PopCount() & 1) == 0;
}

template<size_t Bytes>
bool CPUStorage<Bytes>::HasOddParity() const {
    return (PopCount() & 1) == 1;
}

template<size_t Bytes>
bool CPUStorage<Bytes>::TestBitRange(size_t start, size_t count, bool expectedValue) const {
    for (size_t i = 0; i < count; ++i) {
        size_t bitIndex = start + i;
        if (bitIndex >= totalBits) {
            return false;
        }
        if (GetBit(bitIndex) != expectedValue) {
            return false;
        }
    }
    return true;
}

// ===== IByteAnalyzable Implementation =====

template<size_t Bytes>
std::optional<size_t> CPUStorage<Bytes>::FindByte(uint8_t value, size_t startPos) const {
    for (size_t i = startPos; i < Bytes; ++i) {
        if (data_[i] == value) {
            return i;
        }
    }
    return std::nullopt;
}

template<size_t Bytes>
std::optional<size_t> CPUStorage<Bytes>::FindBytePattern(std::span<const uint8_t> pattern, size_t startPos) const {
    if (pattern.empty() || startPos + pattern.size() > Bytes) {
        return std::nullopt;
    }

    for (size_t i = startPos; i <= Bytes - pattern.size(); ++i) {
        if (std::equal(pattern.begin(), pattern.end(), data_.begin() + i)) {
            return i;
        }
    }
    return std::nullopt;
}

template<size_t Bytes>
int CPUStorage<Bytes>::Compare(const IByteAnalyzable& other) const {
    // This is tricky since we don't know the other's size
    // We'll compare what we can
    // TODO: Maaaaaaaaaaaaaaybe use KMP for this thing?
    size_t minSize = std::min(Bytes, static_cast<size_t>(8)); // Assume reasonable max
    for (size_t i = 0; i < minSize; ++i) {
        // This is a limitation - we can't easily access other's data
        // In a real implementation, you might need a different approach
    }
    return 0; // Placeholder
}

template<size_t Bytes>
int CPUStorage<Bytes>::Compare(std::span<const uint8_t> data) const {
    size_t minSize = std::min(Bytes, data.size());
    int result = std::memcmp(data_.data(), data.data(), minSize);
    if (result != 0) {
        return result;
    }

    // If equal up to minSize, compare sizes
    if (Bytes < data.size()) {
        return -1;
    }
    if (Bytes > data.size()) {
        return 1;
    }
    return 0;
}

template<size_t Bytes>
bool CPUStorage<Bytes>::Equal(const IByteAnalyzable& other) const {
    return Compare(other) == 0;
}

template<size_t Bytes>
bool CPUStorage<Bytes>::Equal(std::span<const uint8_t> data) const {
    return Compare(data) == 0;
}

template<size_t Bytes>
uint32_t CPUStorage<Bytes>::ComputeCRC32() const {
    // Simple CRC32 implementation
    uint32_t crc = 0xFFFFFFFF;
    for (uint8_t byte : data_) {
        crc ^= byte;
        for (int i = 0; i < 8; ++i) {
            crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
        }
    }
    return ~crc;
}

template<size_t Bytes>
uint64_t CPUStorage<Bytes>::ComputeHash() const {
    // Simple FNV-1a hash
    uint64_t hash = 14695981039346656037ULL;
    for (uint8_t byte : data_) {
        hash ^= byte;
        hash *= 1099511628211ULL;
    }
    return hash;
}

// ===== IBitCopyable Implementation =====

template<size_t Bytes>
void CPUStorage<Bytes>::CopyBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) {
    if (srcStart + bitCount > totalBits || dstStart + bitCount > totalBits) {
        return; // Out of bounds
    }

    // Handle overlapping regions
    if (srcStart < dstStart && srcStart + bitCount > dstStart) {
        // Copy backwards to avoid overlap issues
        for (size_t i = bitCount; i > 0; --i) {
            bool bit = GetBit(srcStart + i - 1);
            if (bit) {
                SetBit(dstStart + i - 1);
            }
            else {
                ClearBit(dstStart + i - 1);
            }
        }
    }
    else {
        // Copy forwards
        for (size_t i = 0; i < bitCount; ++i) {
            bool bit = GetBit(srcStart + i);
            if (bit) {
                SetBit(dstStart + i);
            }
            else {
                ClearBit(dstStart + i);
            }
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::MoveBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) {
    CopyBitsInternal(srcStart, bitCount, dstStart);
    // Clear source bits if not overlapping with destination
    if (srcStart >= dstStart + bitCount || srcStart + bitCount <= dstStart) {
        for (size_t i = 0; i < bitCount; ++i) {
            ClearBit(srcStart + i);
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::CopyBitsFrom(const IBitCopyable& source, size_t srcStart, size_t bitCount, size_t dstStart) {
    // This requires the source to be able to provide bit data
    // In practice, you'd need a way to access the source's bits
    // For now, we'll leave this as a placeholder
    throw std::runtime_error("Not implemented");
}

template<size_t Bytes>
void CPUStorage<Bytes>::CopyBitsTo(IBitCopyable& destination, size_t srcStart, size_t bitCount, size_t dstStart) const {
    // Similar issue - we need a way to set bits in the destination
    throw std::runtime_error("Not implemented");
}

template<size_t Bytes>
void CPUStorage<Bytes>::SetBitRange(size_t start, size_t count) {
    // TODO: Maybe Implement Bytewise Value Change
    for (size_t i = 0; i < count; ++i) {
        SetBit(start + i);
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::ClearBitRange(size_t start, size_t count) {
    // TODO: Maybe Implement Bytewise Value Change
    for (size_t i = 0; i < count; ++i) {
        ClearBit(start + i);
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::FlipBitRange(size_t start, size_t count) {
    // TODO: Maybe Implement Bytewise Value Change
    for (size_t i = 0; i < count; ++i) {
        FlipBit(start + i);
    }
}

template<size_t Bytes>
bool CPUStorage<Bytes>::CanCopyBits(const IBitCopyable& source, size_t srcStart, size_t bitCount,
    size_t dstStart) const {
    return dstStart + bitCount <= totalBits;
}

// ===== IByteCopyable Implementation =====

template<size_t Bytes>
void CPUStorage<Bytes>::CopyBytesInternal(size_t srcStart, size_t byteCount, size_t dstStart) {
    if (srcStart + byteCount > Bytes || dstStart + byteCount > Bytes) {
        return;
    }
    std::memmove(data_.data() + dstStart, data_.data() + srcStart, byteCount);
}

template<size_t Bytes>
void CPUStorage<Bytes>::MoveBytesInternal(size_t srcStart, size_t byteCount, size_t dstStart) {
    CopyBytesInternal(srcStart, byteCount, dstStart);
    // Clear source if not overlapping
    if (srcStart >= dstStart + byteCount || srcStart + byteCount <= dstStart) {
        std::memset(data_.data() + srcStart, 0, byteCount);
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::CopyBytesFrom(const IByteCopyable& source, size_t srcStart, size_t byteCount, size_t dstStart) {
    // Implementation depends on being able to access source data
    throw std::runtime_error("Not implemented");
}

template<size_t Bytes>
void CPUStorage<Bytes>::CopyBytesTo(IByteCopyable& destination, size_t srcStart, size_t byteCount,
    size_t dstStart) const {
    // Similar issue - we need a way to access destination data
    throw std::runtime_error("Not implemented");
}

template<size_t Bytes>
void CPUStorage<Bytes>::CopyFromBytes(const uint8_t* data, size_t dataSize, size_t srcStart, size_t dstStart,
    size_t copyCount) {
    if (srcStart + copyCount > dataSize || dstStart + copyCount > Bytes) {
        return;
    }
    std::memcpy(data_.data() + dstStart, data + srcStart, copyCount);
}

template<size_t Bytes>
void CPUStorage<Bytes>::CopyToBytes(uint8_t* data, size_t dataSize, size_t srcStart, size_t dstStart,
    size_t copyCount) const {
    if (srcStart + copyCount > Bytes || dstStart + copyCount > dataSize) {
        return;
    }
    std::memcpy(data + dstStart, data_.data() + srcStart, copyCount);
}

template<size_t Bytes>
void CPUStorage<Bytes>::CopyFromSpan(std::span<const uint8_t> source, size_t dstStart) {
    size_t copyCount = std::min(source.size(), Bytes - dstStart);
    std::memcpy(data_.data() + dstStart, source.data(), copyCount);
}

template<size_t Bytes>
void CPUStorage<Bytes>::CopyToSpan(std::span<uint8_t> destination, size_t srcStart) const {
    size_t copyCount = std::min(destination.size(), Bytes - srcStart);
    std::memcpy(destination.data(), data_.data() + srcStart, copyCount);
}

template<size_t Bytes>
bool CPUStorage<Bytes>::CanCopyBytes(const IByteCopyable& source, size_t srcStart, size_t byteCount,
    size_t dstStart) const {
    return dstStart + byteCount <= Bytes;
}

// ===== IBitManipulable Implementation =====

template<size_t Bytes>
void CPUStorage<Bytes>::ShiftLeft(size_t positions) {
    if (positions >= totalBits) {
        Fill(0x00);
        return;
    }

    // Shift byte by byte for efficiency
    size_t byteShift = positions / 8;
    size_t bitShift = positions % 8;

    if (byteShift > 0) {
        std::memmove(data_.data(), data_.data() + byteShift, Bytes - byteShift);
        std::memset(data_.data() + Bytes - byteShift, 0x00, byteShift);
    }

    if (bitShift > 0) {
        uint8_t carry = 0x00;
        for (size_t i = Bytes; i > 0; --i) {
            uint8_t newCarry = data_[i - 1] >> (8 - bitShift);
            data_[i - 1] = (data_[i - 1] << bitShift) | (carry >> (8 - bitShift));
            carry = newCarry;
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::ShiftRight(size_t positions) {
    if (positions >= totalBits) {
        Fill(0x00);
        return;
    }

    size_t byteShift = positions / 8;
    size_t bitShift = positions % 8;

    if (byteShift > 0) {
        std::memmove(data_.data() + byteShift, data_.data(), Bytes - byteShift);
        std::memset(data_.data(), 0x00, byteShift);
    }

    if (bitShift > 0) {
        uint8_t carry = 0x00;
        for (size_t i = 0; i < Bytes; ++i) {
            uint8_t newCarry = data_[i] << (8 - bitShift);
            data_[i] = (data_[i] >> bitShift) | (carry << (8 - bitShift));
            carry = newCarry;
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::RotateLeft(size_t positions) {
    positions %= totalBits; // Handle rotations larger than size
    if (positions == 0) return;

    // Save the bits that will wrap around
    std::vector<bool> wrapBits(positions);
    for (size_t i = 0; i < positions; ++i) {
        wrapBits[i] = GetBit(totalBits - positions + i);
    }

    // Shift left
    ShiftLeft(positions, false);

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

template<size_t Bytes>
void CPUStorage<Bytes>::RotateRight(size_t positions) {
    positions %= totalBits;
    if (positions == 0) return;

    // Save the bits that will wrap around
    std::vector<bool> wrapBits(positions);
    for (size_t i = 0; i < positions; ++i) {
        wrapBits[i] = GetBit(i);
    }

    // Shift right
    ShiftRight(positions, false);

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

template<size_t Bytes>
void CPUStorage<Bytes>::ReverseBits() {
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

template<size_t Bytes>
void CPUStorage<Bytes>::ReverseBytes() {
    std::reverse(data_.begin(), data_.end());
}

template<size_t Bytes>
void CPUStorage<Bytes>::BitwiseAnd(const IBitManipulable& other) {
    // TODO: This is challenging without knowing the other's concrete type
    // In practice, you might need to add a method to get raw data
    // For now, implement for the same type
    if (auto* other_cpu = dynamic_cast<const CPUStorage<Bytes>*>(&other)) {
        for (size_t i = 0; i < Bytes; ++i) {
            data_[i] &= other_cpu->data_[i];
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::BitwiseOr(const IBitManipulable& other) {
    if (auto* other_cpu = dynamic_cast<const CPUStorage<Bytes>*>(&other)) {
        for (size_t i = 0; i < Bytes; ++i) {
            data_[i] |= other_cpu->data_[i];
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::BitwiseXor(const IBitManipulable& other) {
    if (auto* other_cpu = dynamic_cast<const CPUStorage<Bytes>*>(&other)) {
        for (size_t i = 0; i < Bytes; ++i) {
            data_[i] ^= other_cpu->data_[i];
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::BitwiseNot() {
    for (uint8_t& byte : data_) {
        byte = ~byte;
    }
}

// ===== IByteManipulable Implementation =====

template<size_t Bytes>
void CPUStorage<Bytes>::SwapBytes(size_t index1, size_t index2) {
    if (index1 < Bytes && index2 < Bytes) {
        std::swap(data_[index1], data_[index2]);
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::ReverseByteOrder() {
    std::reverse(data_.begin(), data_.end());
}

template<size_t Bytes>
void CPUStorage<Bytes>::ShiftBytesLeft(size_t positions) {
    if (positions >= Bytes) {
        Fill(0);
        return;
    }

    std::memmove(data_.data(), data_.data() + positions, Bytes - positions);
    std::memset(data_.data() + Bytes - positions, 0, positions);
}

template<size_t Bytes>
void CPUStorage<Bytes>::ShiftBytesRight(size_t positions) {
    if (positions >= Bytes) {
        Fill(0);
        return;
    }

    std::memmove(data_.data() + positions, data_.data(), Bytes - positions);
    std::memset(data_.data(), 0, positions);
}

template<size_t Bytes>
void CPUStorage<Bytes>::ShiftBytesLeft(size_t positions, uint8_t fillValue) {
    if (positions >= Bytes) {
        Fill(fillValue);
        return;
    }

    std::memmove(data_.data(), data_.data() + positions, Bytes - positions);
    std::memset(data_.data() + Bytes - positions, fillValue, positions);
}

template<size_t Bytes>
void CPUStorage<Bytes>::ShiftBytesRight(size_t positions, uint8_t fillValue) {
    if (positions >= Bytes) {
        Fill(fillValue);
        return;
    }

    std::memmove(data_.data() + positions, data_.data(), Bytes - positions);
    std::memset(data_.data(), fillValue, positions);
}

template<size_t Bytes>
void CPUStorage<Bytes>::ToLittleEndian() {
    if constexpr (std::endian::native == std::endian::big) {
        ReverseByteOrder();
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::ToBigEndian() {
    if constexpr (std::endian::native == std::endian::little) {
        ReverseByteOrder();
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::ToNativeEndian() {
    // Already in native endian - no-op
}

template<size_t Bytes>
void CPUStorage<Bytes>::BytewiseAnd(const IByteManipulable& other) {
    // WARN: This works with only the same amount of bytes
    // TODO: Throw some error when they are not the same amount of bytes
    if (auto* other_cpu = dynamic_cast<const CPUStorage<Bytes>*>(&other)) {
        for (size_t i = 0; i < Bytes; ++i) {
            data_[i] &= other_cpu->data_[i];
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::BytewiseOr(const IByteManipulable& other) {
    // TODO: Throw some error when they are not the same amount of bytes
    if (auto* other_cpu = dynamic_cast<const CPUStorage<Bytes>*>(&other)) {
        for (size_t i = 0; i < Bytes; ++i) {
            data_[i] |= other_cpu->data_[i];
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::BytewiseXor(const IByteManipulable& other) {
    // TODO: Throw some error when they are not the same amount of bytes
    if (auto* other_cpu = dynamic_cast<const CPUStorage<Bytes>*>(&other)) {
        for (size_t i = 0; i < Bytes; ++i) {
            data_[i] ^= other_cpu->data_[i];
        }
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::BytewiseNot() {
    for (uint8_t& byte : data_) {
        byte = ~byte;
    }
}

// ===== IStorage Hardware Abstraction =====
template<size_t Bytes>
std::unique_ptr<IStorage> CPUStorage<Bytes>::CreateSimilar(size_t byteSize) const {
    // TODO: Implement this.
    throw std::runtime_error("Not implemented");
}

template<size_t Bytes>
const std::array<uint8_t, Bytes>& CPUStorage<Bytes>::GetData() const {
    return data_;
}

template<size_t Bytes>
std::array<uint8_t, Bytes>& CPUStorage<Bytes>::GetData() {
    return data_;
}

template<size_t Bytes>
void CPUStorage<Bytes>::BitwiseAnd(const CPUStorage<Bytes>& other) {
    for (size_t i = 0; i < Bytes; ++i) {
        data_[i] &= other.data_[i];
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::BitwiseOr(const CPUStorage<Bytes>& other) {
    for (size_t i = 0; i < Bytes; ++i) {
        data_[i] |= other.data_[i];
    }
}

template<size_t Bytes>
void CPUStorage<Bytes>::BitwiseXor(const CPUStorage<Bytes>& other) {
    for (size_t i = 0; i < Bytes; ++i) {
        data_[i] ^= other.data_[i];
    }
}
template<size_t Bytes>
bool CPUStorage<Bytes>::operator==(const CPUStorage<Bytes>& other) const {
    return data_ == other.data_;
}
template<size_t Bytes>
bool CPUStorage<Bytes>::operator!=(const CPUStorage<Bytes>& other) const {
    return data_ != other.data_;
}

template<size_t Bytes>
std::unique_ptr<IStorage> CreateCPUStorage() {
    return std::make_unique<CPUStorage<Bytes> >();
}
