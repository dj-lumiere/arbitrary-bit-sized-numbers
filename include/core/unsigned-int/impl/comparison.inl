//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_COMPARISON_INL
#define ARBITRARYUNSIGNEDINT_COMPARISON_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator==(const ArbitraryUnsignedInt& other) const {
    // Compare only the actual bits that matter
    for (size_t i = 0; i < BitSize; ++i) {
        if (GetBit(BitOffset + i) != other.GetBit(BitOffset + i)) {
            return false;
        }
    }
    return true;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator!=(const ArbitraryUnsignedInt& other) const {
    return !(*this == other);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator<(const ArbitraryUnsignedInt& other) const {
    for (size_t i = BitSize; i > 0; --i) {
        bool thisBit = GetBit(BitOffset + i - 1);
        bool otherBit = other.GetBit(BitOffset + i - 1);

        if (thisBit != otherBit) {
            return thisBit < otherBit; // 0 < 1 is true
        }
    }
    return false; // Equal numbers
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator<=(const ArbitraryUnsignedInt& other) const {
    return (*this < other) || (*this == other);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator>(const ArbitraryUnsignedInt& other) const {
    return !(*this <= other);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
bool ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::operator>=(const ArbitraryUnsignedInt& other) const {
    return !(*this < other);
}

#endif //ARBITRARYUNSIGNEDINT_COMPARISON_INL
