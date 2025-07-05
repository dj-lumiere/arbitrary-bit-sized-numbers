//
// Created by Lumi on 25. 7. 5.
//
#ifndef CPUSTORAGE_BITANALYZABLE_INL
#define CPUSTORAGE_BITANALYZABLE_INL

// BitAnalyzable implementations
template<size_t size>
size_t CPUStorage<size>::PopCount() const {
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        count += std::popcount(data_[i]);
    }
    return count;
}

template<size_t size>
size_t CPUStorage<size>::CountLeadingZeros() const {
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

template<size_t size>
size_t CPUStorage<size>::CountTrailingZeros() const {
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

template<size_t size>
size_t CPUStorage<size>::CountLeadingOnes() const {
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

template<size_t size>
size_t CPUStorage<size>::CountTrailingOnes() const {
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

template<size_t size>
std::optional<size_t> CPUStorage<size>::FindFirstSet() const {
    for (size_t i = 0; i < size; ++i) {
        if (data_[i] != 0) {
            return i * 8 + std::countr_zero(data_[i]);
        }
    }
    return std::nullopt;
}

template<size_t size>
std::optional<size_t> CPUStorage<size>::FindFirstClear() const {
    for (size_t i = 0; i < size; ++i) {
        if (data_[i] != 0xFF) {
            return i * 8 + std::countr_one(data_[i]);
        }
    }
    return std::nullopt;
}

template<size_t size>
std::optional<size_t> CPUStorage<size>::FindLastSet() const {
    for (size_t i = size - 1; i < size; --i) {
        if (data_[i] != 0) {
            return i * 8 + 7 - std::countl_zero(data_[i]);
        }
    }
    return std::nullopt;
}

template<size_t size>
std::optional<size_t> CPUStorage<size>::FindLastClear() const {
    for (size_t i = size - 1; i < size; --i) {
        if (data_[i] != 0xFF) {
            return i * 8 + 7 - std::countl_one(data_[i]);
        }
    }
    return std::nullopt;
}

template<size_t size>
bool CPUStorage<size>::IsAllZeros() const {
    return std::all_of(data_.begin(), data_.end(), [](uint8_t b) { return b == 0; });
}

template<size_t size>
bool CPUStorage<size>::IsAllOnes() const {
    return std::all_of(data_.begin(), data_.end(), [](uint8_t b) { return b == 0xFF; });
}

template<size_t size>
bool CPUStorage<size>::IsPowerOfTwo() const {
    return PopCount() == 1;
}

template<size_t size>
bool CPUStorage<size>::HasEvenParity() const {
    return PopCount() % 2 == 0;
}

template<size_t size>
bool CPUStorage<size>::HasOddParity() const {
    return PopCount() % 2 != 0;
}

template<size_t size>
bool CPUStorage<size>::TestBitRange(size_t start, size_t count, bool expectedValue) const {
    for (size_t i = 0; i < count; ++i) {
        if (GetBit(start + i) != expectedValue) {
            return false;
        }
    }
    return true;
}

#endif //CPUSTORAGE_BITANALYZABLE_INL