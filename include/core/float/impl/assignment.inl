
//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_ASSIGNMENT_INL
#define ARBITRARYFLOAT_ASSIGNMENT_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<typename T, typename>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>& ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator=(T value) {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator=(T value)
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator=(T value) not implemented.");
}

#endif //ARBITRARYFLOAT_ASSIGNMENT_INL
