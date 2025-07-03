//
// Created by Lumi on 25. 6. 20.
//

#ifndef BYTECOPYABLE_H
#define BYTECOPYABLE_H
#include <cstdint>
#include <span>

template<typename T>
concept ByteCopyable = requires(T t, const T ct, size_t start, size_t count, size_t dst,
                                const uint8_t* raw_data, uint8_t* out_data, size_t data_size,
                                std::span<const uint8_t> src_span, std::span<uint8_t> dst_span) {
    // Internal copying (within same object)
    { t.CopyBytesInternal(start, count, dst) } -> std::same_as<void>;
    { t.MoveBytesInternal(start, count, dst) } -> std::same_as<void>;

    // External copying (between objects)
    { t.CopyBytesFrom(ct, start, count, dst) } -> std::same_as<void>;
    { ct.CopyBytesTo(t, start, count, dst) } -> std::same_as<void>;

    // Raw data copying
    { t.CopyFromBytes(raw_data, data_size, start, dst, count) } -> std::same_as<void>;
    { ct.CopyToBytes(out_data, data_size, start, dst, count) } -> std::same_as<void>;

    // Span operations
    { t.CopyFromSpan(src_span, dst) } -> std::same_as<void>;
    { ct.CopyToSpan(dst_span, start) } -> std::same_as<void>;

    // Validation
    { ct.CanCopyBytes(ct, start, count, dst) } -> std::convertible_to<bool>;
};

#endif //BYTECOPYABLE_H
