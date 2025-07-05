//
// Created by Lumi on 25. 7. 5.
//

#ifndef COMPARISON_INL
#define COMPARISON_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator==(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator!=(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator<(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator<=(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator>(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator>=(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
std::partial_ordering ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator<=>(const ArbitraryFloat& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator==(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator!=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator<(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator<=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator>(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
bool ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator>=(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t OtherExpBits, size_t OtherMantBits, typename OtherStorageProvider>
std::partial_ordering ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator<=>(const ArbitraryFloat<OtherExpBits, OtherMantBits, OtherStorageProvider>& other) const {
}
#endif //COMPARISON_INL
