//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_CONSTRUTORS_INL
#define ARBITRARYFLOAT_CONSTRUTORS_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(float value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(float value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(float value) not implemented.");
}

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(double value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(double value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(double value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(long double value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(long double value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(long double value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(T value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(T value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(T value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(const std::string& str) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(const std::string& str)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(const std::string& str) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t BitSize, size_t BitOffset, typename IntStorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntStorageProviderType>& value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider>& value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::ArbitraryFloat(const ArbitrarySignedInt<BitSize, BitOffset, IntStorageProvider>& value) not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t BitSize, size_t BitOffset, typename UIntStorageProviderType> requires StorageProvider<UIntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, UIntStorageProviderType>& value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider>& value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::ArbitraryFloat(const ArbitraryUnsignedInt<BitSize, BitOffset, IntStorageProvider>& value) not implemented.");
}

#endif //ARBITRARYFLOAT_CONSTRUTORS_INL
