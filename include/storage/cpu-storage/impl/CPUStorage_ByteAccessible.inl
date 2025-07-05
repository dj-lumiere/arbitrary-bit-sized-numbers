//
// Created by Lumi on 25. 7. 5.
//

#ifndef CPUSTORAGE_BYTEACCESSIBLE_INL
#define CPUSTORAGE_BYTEACCESSIBLE_INL

// ByteAccessible implementations
template<size_t size>
uint8_t& CPUStorage<size>::operator[](size_t index) {
    if (index >= size)
        throw std::out_of_range("Index out of bounds");
    return data_[index];
}

template<size_t size>
const uint8_t& CPUStorage<size>::operator[](size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of bounds");
    return data_[index];
}

template<size_t size>
uint8_t* CPUStorage<size>::Data() {
    return data_.data();
}

template<size_t size>
const uint8_t* CPUStorage<size>::Data() const {
    return data_.data();
}

template<size_t size>
constexpr size_t CPUStorage<size>::GetByteSize() const {
    return size;
}

template<size_t size>
void CPUStorage<size>::Fill(uint8_t value) {
    data_.fill(value);
}

template<size_t size>
void CPUStorage<size>::Clear() {
    data_.fill(0);
}

#endif //CPUSTORAGE_BYTEACCESSIBLE_INL