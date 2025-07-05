//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYFLOAT_UNARY_OPS_INL
#define ARBITRARYFLOAT_UNARY_OPS_INL

template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator+() const {
    return *this;
}
template<size_t ExpBits, size_t MantissaBits, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((ExpBits + MantissaBits + 1 + 7) >> 3)>
ArbitraryFloat<ExpBits, MantissaBits, StorageProviderType>::operator-() const {
    return this->SetSignBit(!this->GetSignBit());
}

#endif //ARBITRARYFLOAT_UNARY_OPS_INL
