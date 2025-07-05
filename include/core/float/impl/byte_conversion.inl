
//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_BYTE_CONVERSION_INL
#define ARBITRARYFLOAT_BYTE_CONVERSION_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ToBeBytes() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ToLeBytes() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ToNeBytes() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::FromBeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::FromLeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType> ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::FromNeBytes(const std::array<uint8_t, ((ExpBits + MantissaBits + 1 + 7) >> 3)>& bytes) {
}

#endif //ARBITRARYFLOAT_BYTE_CONVERSION_INL
