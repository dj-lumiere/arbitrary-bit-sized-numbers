//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_ARITHMETIC_INL
#define ARBITRARYFLOAT_ARITHMETIC_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator+(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator+(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator-(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator-(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator*(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator*(const ArbitraryFloat& other) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator/(const ArbitraryFloat& other) const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator/(const ArbitraryFloat& other) not implemented.");
}

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
auto ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator+(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const -> ArbitraryFloat<std::max(ExpBits, OtherExpBits), std::max(MantissaBits, OtherMantBits), StorageProviderType> {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
auto ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator-(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const -> ArbitraryFloat<std::max(ExpBits, OtherExpBits), std::max(MantissaBits, OtherMantBits), StorageProviderType> {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
auto ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator*(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const -> ArbitraryFloat<std::max(ExpBits, OtherExpBits), std::max(MantissaBits, OtherMantBits), StorageProviderType> {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
auto ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator/(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const -> ArbitraryFloat<std::max(ExpBits, OtherExpBits), std::max(MantissaBits, OtherMantBits), StorageProviderType> {
}

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator+=(const ArbitraryFloat& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator-=(const ArbitraryFloat& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator*=(const ArbitraryFloat& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator/=(const ArbitraryFloat& other) {
}

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator+=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator-=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator*=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator/=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) {
}
#endif //ARBITRARYFLOAT_ARITHMETIC_INL
