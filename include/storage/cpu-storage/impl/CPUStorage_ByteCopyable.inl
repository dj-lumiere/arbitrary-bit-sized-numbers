//
// Created by Lumi on 25. 7. 5.
//

#ifndef CPUSTORAGE_BYTECOPYABLE_INL
#define CPUSTORAGE_BYTECOPYABLE_INL

// ByteCopyable implementations
template<size_t size>
void CPUStorage<size>::CopyBytesInternal(size_t srcStart, size_t count, size_t dst) {
    std::copy(data_.begin() + srcStart, data_.begin() + srcStart + count, data_.begin() + dst);
}

template<size_t size>
void CPUStorage<size>::MoveBytesInternal(size_t srcStart, size_t count, size_t dst) {
    std::move(data_.begin() + srcStart, data_.begin() + srcStart + count, data_.begin() + dst);
}

template<size_t size>
template<size_t OtherSize>
void CPUStorage<size>::CopyBytesFrom(const CPUStorage<OtherSize>& source, size_t srcStart, size_t count, size_t dst) {
    std::copy(source.data_.begin() + srcStart, source.data_.begin() + srcStart + count, data_.begin() + dst);
}

template<size_t size>
template<size_t OtherSize>
void CPUStorage<size>::CopyBytesTo(CPUStorage<OtherSize>& destination, size_t srcStart, size_t count, size_t dst) const {
    std::copy(data_.begin() + srcStart, data_.begin() + srcStart + count, destination.data_.begin() + dst);
}

template<size_t size>
void CPUStorage<size>::CopyFromBytes(const uint8_t* src, size_t srcByteSize, size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) {
    std::copy(src + srcOffsetBytes, src + srcOffsetBytes + countBytes, data_.begin() + dstOffsetBytes);
}

template<size_t size>
void CPUStorage<size>::CopyToBytes(uint8_t* dst, size_t dstByteSize, size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) const {
    std::copy(data_.begin() + srcOffsetBytes, data_.begin() + srcOffsetBytes + countBytes, dst + dstOffsetBytes);
}

template<size_t size>
void CPUStorage<size>::CopyFromSpan(std::span<const uint8_t> src_span, size_t dst) {
    std::copy(src_span.begin(), src_span.end(), data_.begin() + dst);
}

template<size_t size>
void CPUStorage<size>::CopyToSpan(std::span<uint8_t> dst_span, size_t start) const {
    std::copy(data_.begin() + start, data_.begin() + start + dst_span.size(), dst_span.begin());
}

template<size_t size>
template<size_t OtherSize>
bool CPUStorage<size>::CanCopyBytes(const CPUStorage<OtherSize>& source, size_t srcStart, size_t count, size_t dst) const {
    return srcStart + count <= source.GetByteSize() && dst + count <= GetByteSize();
}
template<size_t size>
void CPUStorage<size>::MoveBytes(size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) {
    MoveBytesInternal(srcOffsetBytes, countBytes, dstOffsetBytes);
}

template<size_t size>
bool CPUStorage<size>::CanCopyBytes(size_t srcOffsetBytes, size_t dstOffsetBytes, size_t countBytes) const {
    return srcOffsetBytes + countBytes <= size && dstOffsetBytes + countBytes <= size;
}

#endif //CPUSTORAGE_BYTECOPYABLE_INL