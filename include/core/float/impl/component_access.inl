//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_COMPONENT_ACCESS_INL
#define ARBITRARYFLOAT_COMPONENT_ACCESS_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::GetSignBit() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
void ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::SetSignBit(bool sign) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t ExpSize, size_t ExpOffset, typename ExpStorageProviderType>
ArbitraryUnsignedInt<ExpSize, ExpOffset, ExpStorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::GetRawExponent() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t ExpSize, size_t ExpOffset, typename ExpStorageProviderType>
ArbitrarySignedInt<ExpSize, ExpOffset, ExpStorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::GetExponent() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t MantSize, size_t MantOffset, typename MantStorageProviderType>
ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::GetMantissa() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t MantSize, size_t MantOffset, typename MantStorageProviderType>
ArbitraryUnsignedInt<MantSize, MantOffset, MantStorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::GetSignificand() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::FromComponents(bool sign, uint64_t exponent, uint64_t mantissa) {
}

#endif //ARBITRARYFLOAT_COMPONENT_ACCESS_INL
