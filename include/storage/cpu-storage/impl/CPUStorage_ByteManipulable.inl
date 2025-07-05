//
// Created by Lumi on 25. 7. 5.
//

#ifndef CPUSTORAGE_BYTEMANIPULABLE_INL
#define CPUSTORAGE_BYTEMANIPULABLE_INL

// ByteManipulable implementations
template<size_t size>
void CPUStorage<size>::SwapBytes(size_t index1, size_t index2) {
    std::swap(data_[index1], data_[index2]);
}

template<size_t size>
void CPUStorage<size>::ReverseByteOrder() {
    std::reverse(data_.begin(), data_.end());
}

template<size_t size>
void CPUStorage<size>::ShiftBytesLeft(size_t positions) {
    if (positions >= size) {
        data_.fill(0);
        return;
    }
    std::memmove(data_.data() + positions, data_.data(), size - positions);
    std::memset(data_.data(), 0, positions);
}

template<size_t size>
void CPUStorage<size>::ShiftBytesRight(size_t positions) {
    if (positions >= size) {
        data_.fill(0);
        return;
    }
    std::memmove(data_.data(), data_.data() + positions, size - positions);
    std::memset(data_.data() + size - positions, 0, positions);
}

template<size_t size>
void CPUStorage<size>::ShiftBytesLeft(size_t positions, uint8_t fillValue) {
    if (positions >= size) {.
        data_.fill(fillValue);
        return;
    }
    std::memmove(data_.data() + positions, data_.data(), size - positions);
    std::memset(data_.data(), fillValue, positions);
}

template<size_t size>
void CPUStorage<size>::ShiftBytesRight(size_t positions, uint8_t fillValue) {
    if (positions >= size) {
        data_.fill(fillValue);
        return;
    }
    std::memmove(data_.data(), data_.data() + positions, size - positions);
    std::memset(data_.data() + size - positions, fillValue, positions);
}

template<size_t size>
void CPUStorage<size>::ToLittleEndian() {
    // Already in little endian on most systems, but implement for completeness
}

template<size_t size>
void CPUStorage<size>::ToBigEndian() {
    ReverseByteOrder();
}

template<size_t size>
void CPUStorage<size>::ToNativeEndian() {
    // Assume native is little endian
}

template<size_t size>
void CPUStorage<size>::BytewiseAnd(const CPUStorage& other) {
    for (size_t i = 0; i < size; ++i) {
        data_[i] &= other.data_[i];
    }
}

template<size_t size>
void CPUStorage<size>::BytewiseOr(const CPUStorage& other) {
    for (size_t i = 0; i < size; ++i) {
        data_[i] |= other.data_[i];
    }
}

template<size_t size>
void CPUStorage<size>::BytewiseXor(const CPUStorage& other) {
    for (size_t i = 0; i < size; ++i) {
        data_[i] ^= other.data_[i];
    }
}

template<size_t size>
void CPUStorage<size>::BytewiseNot() {
    for (size_t i = 0; i < size; ++i) {
        data_[i] = ~data_[i];
    }
}

#endif //CPUSTORAGE_BYTEMANIPULABLE_INL