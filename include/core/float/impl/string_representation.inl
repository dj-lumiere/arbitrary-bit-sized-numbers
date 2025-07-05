//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_STRING_REPRESENTATION_INL
#define ARBITRARYFLOAT_STRING_REPRESENTATION_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ToString() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::BitRepresentation() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ToDecimalString() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ToHexString() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ToScientificString() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::string ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ToScientificString(int precision) const {
}

#endif //ARBITRARYFLOAT_STRING_REPRESENTATION_INL
