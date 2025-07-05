//
// Created by Lumi on 25. 7. 5.
//

#ifndef CPUSTORAGE_BYTEANALYZABLE_INL
#define CPUSTORAGE_BYTEANALYZABLE_INL

// ByteAnalyzable implementations
template<size_t size>
std::optional<size_t> CPUStorage<size>::FindByte(uint8_t value, size_t startPos) const {
    auto it = std::find(data_.begin() + startPos, data_.end(), value);
    if (it != data_.end()) {
        return std::distance(data_.begin(), it);
    }
    return std::nullopt;
}

template<size_t size>
std::optional<size_t> CPUStorage<size>::FindBytePattern(std::span<const uint8_t> pattern, size_t startPos) const {
    auto it = std::search(data_.begin() + startPos, data_.end(), pattern.begin(), pattern.end());
    if (it != data_.end()) {
        return std::distance(data_.begin(), it);
    }
    return std::nullopt;
}

template<size_t size>
int CPUStorage<size>::Compare(const CPUStorage& other) const {
    return std::memcmp(data_.data(), other.data_.data(), size);
}

template<size_t size>
int CPUStorage<size>::Compare(std::span<const uint8_t> data) const {
    return std::memcmp(data_.data(), data.data(), std::min(size, data.size()));
}

template<size_t size>
bool CPUStorage<size>::Equal(const CPUStorage& other) const {
    return data_ == other.data_;
}

template<size_t size>
bool CPUStorage<size>::Equal(std::span<const uint8_t> data) const {
    return std::equal(data_.begin(), data_.end(), data.begin(), data.end());
}

template<size_t size>
uint32_t CPUStorage<size>::ComputeCRC32() const {
    // Not implemented
    return 0;
}

template<size_t size>
uint64_t CPUStorage<size>::ComputeHash() const {
    // Not implemented
    return 0;
}

#endif //CPUSTORAGE_BYTEANALYZABLE_INL