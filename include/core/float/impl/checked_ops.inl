//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_CHECKED_OPS_INL
#define ARBITRARYFLOAT_CHECKED_OPS_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::CheckedAdd(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::CheckedSub(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::CheckedMul(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::optional<ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::CheckedDiv(const ArbitraryFloat& other) const {
}

#endif //ARBITRARYFLOAT_CHECKED_OPS_INL
