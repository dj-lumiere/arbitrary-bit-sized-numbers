//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_HYPERBOLIC_INL
#define ARBITRARYFLOAT_HYPERBOLIC_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Sinh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Cosh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Tanh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Asinh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Acosh() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Atanh() const {
}

#endif //ARBITRARYFLOAT_HYPERBOLIC_INL
