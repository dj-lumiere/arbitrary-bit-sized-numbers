//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_FUSED_OPS_INL
#define ARBITRARYFLOAT_FUSED_OPS_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Fma(const ArbitraryFloat& y, const ArbitraryFloat& z) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Fms(const ArbitraryFloat& y, const ArbitraryFloat& z) const {
}

#endif //ARBITRARYFLOAT_FUSED_OPS_INL
