//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_EXPONENTIAL_LOGARITHMIC_INL
#define ARBITRARYFLOAT_EXPONENTIAL_LOGARITHMIC_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Exp() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Exp2() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Exp10() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Expm1() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Log() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Log2() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Log10() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Log1p() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Logb(const ArbitraryFloat& b) const {
}

#endif //ARBITRARYFLOAT_EXPONENTIAL_LOGARITHMIC_INL
