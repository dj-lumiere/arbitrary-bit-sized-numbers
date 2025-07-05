//
// Created by Lumi on 25. 7. 5.
//

#ifndef CPUSTORAGE_BITMANIPULABLE_INL
#define CPUSTORAGE_BITMANIPULABLE_INL

// BitManipulable implementations
template<size_t size>
void CPUStorage<size>::ShiftLeft(size_t positions) {
    if (positions == 0) {
        return;
    }

    size_t byteOffset = positions >> 3;
    size_t bitOffset = positions & 7;

    if (bitOffset != 0) {
        // Process from HIGH to LOW bytes (right to left)
        for (size_t i = size - 1; i >= 1; --i) {
            data_[i] <<= bitOffset;
            data_[i] |= data_[i - 1] >> (8 - bitOffset); // Get carry from lower byte
        }
        // Handle the lowest byte (no carry from below)
        data_[0] <<= bitOffset;
    }

    ShiftBytesLeft(byteOffset);
}

template<size_t size>
void CPUStorage<size>::ShiftRight(size_t positions) {
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

template<size_t size>
void CPUStorage<size>::RotateLeft(size_t positions) {
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

template<size_t size>
void CPUStorage<size>::RotateRight(size_t positions) {
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

template<size_t size>
void CPUStorage<size>::ReverseBits() {
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

template<size_t size>
void CPUStorage<size>::ReverseBytes() {
    std::reverse(data_.begin(), data_.end());
}

template<size_t size>
void CPUStorage<size>::BitwiseAnd(const CPUStorage& other) {
    for (size_t i = 0; i < size; ++i) {
        data_[i] &= other.data_[i];
    }
}

template<size_t size>
void CPUStorage<size>::BitwiseOr(const CPUStorage& other) {
    for (size_t i = 0; i < size; ++i) {
        data_[i] |= other.data_[i];
    }
}

template<size_t size>
void CPUStorage<size>::BitwiseXor(const CPUStorage& other) {
    for (size_t i = 0; i < size; ++i) {
        data_[i] ^= other.data_[i];
    }
}

template<size_t size>
void CPUStorage<size>::BitwiseNot() {
    for (size_t i = 0; i < size; ++i) {
        data_[i] = ~data_[i];
    }
}

template<size_t size>
void CPUStorage<size>::Increment() {
    for (size_t i = 0; i < size; ++i) {
        if (++data_[i] != 0) {
            break;
        }
    }
}

template<size_t size>
void CPUStorage<size>::Decrement() {
    for (size_t i = 0; i < size; ++i) {
        if (--data_[i] != 0xFF) {
            break;
        }
    }
}

template<size_t size>
void CPUStorage<size>::OffsetAdd(size_t offset, size_t bitWidth, size_t value) {
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

template<size_t size>
void CPUStorage<size>::OffsetSub(size_t offset, size_t bitWidth, size_t value) {
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

template<size_t size>
template<size_t OtherSize>
void CPUStorage<size>::OffsetAdd(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart) {
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

template<size_t size>
template<size_t OtherSize>
void CPUStorage<size>::OffsetSub(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart) {
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

template<size_t size>
std::pair<CPUStorage<size>, bool> CPUStorage<size>::OffsetAddWithCarry(size_t offset, size_t bitWidth, size_t value, bool initialCarry) {
    if (offset + bitWidth > totalBits) {
        throw std::out_of_range("Bit range out of bounds in OffsetAddWithCarry");
    }

    CPUStorage<size> temp_storage = *this;
    bool carry = initialCarry;
    for (size_t i = 0; i < bitWidth; ++i) {
        bool current_bit = temp_storage.GetBit(offset + i);
        bool value_bit = (value >> i) & 1;

        bool sum_bit = current_bit ^ value_bit ^ carry;
        carry = (current_bit && value_bit) || (current_bit && carry) || (value_bit && carry);

        temp_storage.SetBit(offset + i, sum_bit);
    }
    return { temp_storage, carry };
}

template<size_t size>
std::pair<CPUStorage<size>, bool> CPUStorage<size>::OffsetSubWithBorrow(size_t offset, size_t bitWidth, size_t value, bool initialBorrow) {
    if (offset + bitWidth > totalBits) {
        throw std::out_of_range("Bit range out of bounds in OffsetSubWithBorrow");
    }

    CPUStorage<size> temp_storage = *this;
    bool borrow = initialBorrow;
    for (size_t i = 0; i < bitWidth; ++i) {
        bool current_bit = temp_storage.GetBit(offset + i);
        bool value_bit = (value >> i) & 1;

        bool diff_bit = current_bit ^ value_bit ^ borrow;
        borrow = (!current_bit && value_bit) || (!current_bit && borrow) || (value_bit && borrow);

        temp_storage.SetBit(offset + i, diff_bit);
    }
    return { temp_storage, borrow };
}

template<size_t size>
template<size_t OtherSize>
std::pair<CPUStorage<size>, bool> CPUStorage<size>::OffsetAddWithCarry(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart, bool initialCarry) {
    if (srcStart + srcWidth > ct.totalBits) {
        throw std::out_of_range("Source bit range out of bounds in OffsetAddWithCarry (CPUStorage overload)");
    }

    CPUStorage<size> temp_storage = *this;
    bool carry = initialCarry;
    for (size_t i = 0; i < srcWidth; ++i) {
        if (dstStart + i >= totalBits) {
            // Discard leftover bits
            break;
        }
        bool current_dst_bit = temp_storage.GetBit(dstStart + i);
        bool src_bit = ct.GetBit(srcStart + i);

        bool sum_bit = current_dst_bit ^ src_bit ^ carry;
        carry = (current_dst_bit && src_bit) || (current_dst_bit && carry) || (src_bit && carry);

        temp_storage.SetBit(dstStart + i, sum_bit);
    }
    return { temp_storage, carry };
}

template<size_t size>
template<size_t OtherSize>
std::pair<CPUStorage<size>, bool> CPUStorage<size>::OffsetSubWithBorrow(const CPUStorage<OtherSize>& ct, size_t srcStart, size_t srcWidth, size_t dstStart, bool initialBorrow) {
    if (srcStart + srcWidth > ct.totalBits) {
        throw std::out_of_range("Source bit range out of bounds in OffsetSubWithBorrow (CPUStorage overload)");
    }

    CPUStorage<size> temp_storage = *this;
    bool borrow = initialBorrow;
    for (size_t i = 0; i < srcWidth; ++i) {
        if (dstStart + i >= totalBits) {
            // Discard leftover bits
            break;
        }
        bool current_dst_bit = temp_storage.GetBit(dstStart + i);
        bool src_bit = ct.GetBit(srcStart + i);

        bool diff_bit = current_dst_bit ^ src_bit ^ borrow;
        borrow = (!current_dst_bit && src_bit) || (!current_dst_bit && borrow) || (src_bit && borrow);

        temp_storage.SetBit(dstStart + i, diff_bit);
    }
    return { temp_storage, borrow };
}

#endif //CPUSTORAGE_BITMANIPULABLE_INL