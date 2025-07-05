//
// Created by Lumi on 25. 7. 5.
//

#ifndef CONVERSIONS_INL
#define CONVERSIONS_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator float() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator float() const
    throw std::runtime_error("ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator float() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator double() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator double() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator long double() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator long double() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator long long() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator long long() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator unsigned long long() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned long long() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator int() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator int() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator unsigned int() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned int() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator short() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator short() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator unsigned short() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned short() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator char() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator char() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator unsigned char() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator unsigned char() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator bool() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProvider>::operator bool() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t NewExp, size_t NewMant, typename NewStorageProviderType> requires StorageProvider<NewStorageProviderType, ((NewExp + NewMant + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator ArbitraryFloat<NewExp, NewMant, NewStorageProviderType>() const {
    // TODO: Implement ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator ArbitraryFloat<NewExp, NewMant, NewStorageProviderType>() not implemented.");
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t BitSize, size_t BitOffset, typename IntStorageProviderType> requires StorageProvider<IntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator ArbitrarySignedInt<BitSize, BitOffset, IntStorageProviderType>() const {
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
template<size_t BitSize, size_t BitOffset, typename UIntStorageProviderType> requires StorageProvider<UIntStorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator ArbitraryUnsignedInt<BitSize, BitOffset, UIntStorageProviderType>() const {
}

#endif //CONVERSIONS_INL
