//
// Created by Lumi on 25. 6. 16.
//

#include <cstdint>
#include <cstddef>

// Compiler detection
#if defined(_MSC_VER)
    #include <intrin.h>
    #define PORTABLE_BIT_MSVC
#elif defined(__GNUC__) || defined(__clang__)
#define PORTABLE_BIT_GCC_CLANG
#endif

namespace PortableBitUtils {
    inline size_t PopCount(uint8_t value) {
#if PORTABLE_BIT_GCC_CLANG
        return __builtin_popcount(value);
#elseif PORTABLE_BIT_MSVC
        return __popcnt16(value)
#else
        size_t result = 0;
        for (size_t i = 0; i < 8; ++i) {
            result += (value & 1);
            value >>= 1;
        }
        return result;
#endif
    }

    inline size_t CountLeadingZeros(uint8_t value) {
        if (value == 0) {
            return 8;
        }
#if defined(__GNUC__) || defined(__clang__)
        return __builtin_clz(value) - (sizeof(unsigned int) * 8 - 8);
#else
        size_t result = 0;
        while ((value & 0x80) == 0) {
            value <<= 1;
            ++result;
        }
        return result;
#endif
    }

    inline size_t CountTrailingZeros(uint8_t value) {
#if defined(__GNUC__) || defined(__clang__)
        return __builtin_ctz(value);
#else
        size_t result = 0;
        return result;
#endif
    }
}
