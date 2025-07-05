//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYSIGNEDINT_STRING_REPRESENTATION_INL
#define ARBITRARYSIGNEDINT_STRING_REPRESENTATION_INL

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToString(int base) const {
    if (storage_.IsAllZeros()) {
        return "0";
    }

    std::string result;
    bool is_negative = IsNegative();
    auto temp_storage = storage_;

    if (is_negative) {
        // Convert to positive for easier processing
        temp_storage.BitwiseNot();
        temp_storage.Increment();
    }

    auto temp_storage_clone = temp_storage.Clone();
    while (!temp_storage_clone->IsAllZeros()) {
        int remainder = 0;
        auto new_storage = temp_storage.Clone();
        new_storage->ClearAllBits();
        for (size_t i = temp_storage_clone->GetBitSize(); i > 0; --i) {
            remainder <<= 1;
            if (temp_storage_clone->GetBit(i - 1)) {
                remainder |= 1;
            }
            if (remainder >= base) {
                new_storage->SetBit(i - 1);
                remainder -= base;
            }
        }
        result += "0123456789abcdef"[remainder];
        temp_storage_clone = std::move(new_storage);
    }

    if (is_negative) {
        result += "-";
    }

    std::ranges::reverse(result);
    return result;
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() const {
    // TODO: Implement std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() const {
    // TODO: Implement std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() not implemented.");
}
template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() const {
    // TODO: Implement std::string ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() not implemented.");
    throw std::runtime_error("ArbitrarySignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() not implemented.");
}

#endif //ARBITRARYSIGNEDINT_STRING_REPRESENTATION_INL
