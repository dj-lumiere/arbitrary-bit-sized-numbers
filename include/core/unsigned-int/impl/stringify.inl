//
// Created by Lumi on 25. 7. 5.
//

#ifndef ARBITRARYUNSIGNEDINT_STRINGIFY_INL
#define ARBITRARYUNSIGNEDINT_STRINGIFY_INL
#include <algorithm>

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToString(int base) const {
    if (base < 2 || base > 36) {
        throw std::invalid_argument("Base must be between 2 and 36");
    }

    if (this->IsZero()) {
        return "0";
    }

    std::string result;
    ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType> temp = *this;
    while (!temp.IsZero()) {
        auto [quotient, remainder] = temp.DivRem(base);
        temp = std::move(quotient);

        // Convert remainder to integer for character conversion
        unsigned int digit = static_cast<unsigned int>(remainder); // ✅ This should work if you have operator int()

        if (digit < 10) {
            result += '0' + digit;
        }
        else {
            result += 'A' + (digit - 10); // ✅ Handle bases > 10
        }
    }
    std::ranges::reverse(result);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToBinaryString() const {
    std::string result;

    for (size_t i = 0; i < BitSize; ++i) {
        result += GetBit(BitOffset + i) ?
                      '1' :
                      '0';
    }
    std::ranges::reverse(result);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::ToHexString() const {
    std::string result;
    uint8_t nibble = 0;
    for (size_t i = 0; i < BitSize; ++i) {
        nibble <<= 1;
        nibble |= GetBit(BitOffset + i);
        if (i & 3 == 3) {
            result += nibble < 10 ?
                          '0' + nibble :
                          'A' + (nibble - 10);
            nibble = 0;
        }
    }
    std::ranges::reverse(result);
    return result;
}

template<size_t BitSize, size_t BitOffset, typename StorageProviderType> requires StorageProvider<StorageProviderType, ((BitSize + BitOffset + 7) >> 3)>
std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() const {
    // TODO: Implement std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() const
    throw std::runtime_error("std::string ArbitraryUnsignedInt<BitSize, BitOffset, StorageProviderType>::BitRepresentation() const not implemented.");
}

#endif //ARBITRARYUNSIGNEDINT_STRINGIFY_INL
