//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_WRAPPING_OPS_INL
#define ARBITRARYUNSIGNEDINT_WRAPPING_OPS_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingAdd(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this + other.
    return *this + other;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingSub(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this - other.
    return *this - other;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingMul(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this * other.
    return *this * other;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingDiv(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this / other.
    return *this / other;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingRem(const ArbitraryUnsignedInt& other) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns this % other.
    return *this % other;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingPow(const ArbitraryUnsignedInt& exp) const {
    // In ArbitraryUnsignedInt, the default method for processing overflow is wrapping mode,
    // so it just returns pow(this, other).
    return pow(*this, exp);
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShl(size_t shift) not implemented.");
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) const {
    // TODO: Implement ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) const
    throw std::runtime_error("ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::WrappingShr(size_t shift) not implemented.");
}

#endif //ARBITRARYUNSIGNEDINT_WRAPPING_OPS_INL
