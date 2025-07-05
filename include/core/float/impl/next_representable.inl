//
// Created by Lumi on 25. 7. 5.
//

#ifndef NEXT_REPRESENTABLE_INL
#define NEXT_REPRESENTABLE_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::NextUp() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::NextDown() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::NextAfter(const ArbitraryFloat& direction) const {
}

#endif //NEXT_REPRESENTABLE_INL
