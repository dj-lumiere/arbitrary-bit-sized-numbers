//
// Created by Lumi on 25. 7. 5.
//

#ifndef CPUSTORAGE_BITACCESSIBLE_INL
#define CPUSTORAGE_BITACCESSIBLE_INL
// BitAccessible implementations
template<size_t size>
bool CPUStorage<size>::GetBit(const size_t bitIndex) const {
    if (bitIndex >= size * 8)
        throw std::out_of_range("Bit index out of bounds");
    return (data_[bitIndex / 8] >> (bitIndex % 8)) & 1;
}

template<size_t size>
void CPUStorage<size>::SetBit(const size_t bitIndex) {
    if (bitIndex >= size * 8)
        throw std::out_of_range("Bit index out of bounds");
    data_[bitIndex / 8] |= (1 << (bitIndex % 8));
}

template<size_t size>
void CPUStorage<size>::SetBit(const size_t bitIndex, const bool value) {
    if (value)
        SetBit(bitIndex);
    else
        ClearBit(bitIndex);
}

template<size_t size>
void CPUStorage<size>::ClearBit(const size_t bitIndex) {
    if (bitIndex >= size * 8)
        throw std::out_of_range("Bit index out of bounds");
    data_[bitIndex / 8] &= ~(1 << (bitIndex % 8));
}

template<size_t size>
void CPUStorage<size>::FlipBit(const size_t bitIndex) {
    if (bitIndex >= size * 8)
        throw std::out_of_range("Bit index out of bounds");
    data_[bitIndex / 8] ^= (1 << (bitIndex % 8));
}

template<size_t size>
void CPUStorage<size>::SetAllBits() {
    data_.fill(0xFF);
}

template<size_t size>
void CPUStorage<size>::ClearAllBits() {
    data_.fill(0x00);
}

template<size_t size>
void CPUStorage<size>::FlipAllBits() {
    for (size_t i = 0; i < size; ++i) {
        data_[i] = ~data_[i];
    }
}

template<size_t size>
constexpr size_t CPUStorage<size>::GetBitSize() const {
    return size * 8;
}

#endif //CPUSTORAGE_BITACCESSIBLE_INL
