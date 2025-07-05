//
// Created by Lumi on 25. 7. 5.
//

#ifndef CPUSTORAGE_BITCOPYABLE_INL
#define CPUSTORAGE_BITCOPYABLE_INL

// BitCopyable implementations
template<size_t size>
void CPUStorage<size>::CopyBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) {
    for (size_t i = 0; i < bitCount; ++i) {
        SetBit(dstStart + i, GetBit(srcStart + i));
    }
}

template<size_t size>
void CPUStorage<size>::MoveBitsInternal(size_t srcStart, size_t bitCount, size_t dstStart) {
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

template<size_t size>
template<size_t OtherSize>
void CPUStorage<size>::CopyBitsFrom(const CPUStorage<OtherSize>& source, size_t srcStart, size_t bitCount, size_t dstStart) {
    for (size_t i = 0; i < bitCount; ++i) {
        SetBit(dstStart + i, source.GetBit(srcStart + i));
    }
}

template<size_t size>
template<size_t OtherSize>
void CPUStorage<size>::CopyBitsTo(CPUStorage<OtherSize>& destination, size_t srcStart, size_t bitCount, size_t dstStart) const {
    for (size_t i = 0; i < bitCount; ++i) {
        destination.SetBit(dstStart + i, GetBit(srcStart + i));
    }
}

template<size_t size>
void CPUStorage<size>::SetBitRange(size_t start, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        SetBit(start + i);
    }
}

template<size_t size>
void CPUStorage<size>::ClearBitRange(size_t start, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        ClearBit(start + i);
    }
}

template<size_t size>
void CPUStorage<size>::FlipBitRange(size_t start, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        FlipBit(start + i);
    }
}

template<size_t size>
template<size_t OtherSize>
bool CPUStorage<size>::CanCopyBits(const CPUStorage<OtherSize>& source, size_t srcStart, size_t bitCount, size_t dstStart) const {
    return srcStart + bitCount <= source.GetByteSize() * 8 && dstStart + bitCount <= GetByteSize() * 8;
}

#endif //CPUSTORAGE_BITCOPYABLE_INL