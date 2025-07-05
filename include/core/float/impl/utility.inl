//
// Created by Lumi on 25. 7. 5.
//

#ifndef UTILITY_INL
#define UTILITY_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
void ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::Normalize() {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::IsSpecialValue() const {
}

#endif //UTILITY_INL
