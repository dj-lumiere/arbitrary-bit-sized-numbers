//
// Created by Lumi on 25. 6. 20.
//

#ifndef BITCOPYABLE_H
#define BITCOPYABLE_H

template<typename T>
concept BitCopyable = requires(T t, const T ct, size_t start, size_t count, size_t dst) {
    // Internal copying
    { t.CopyBitsInternal(start, count, dst) } -> std::same_as<void>;
    { t.MoveBitsInternal(start, count, dst) } -> std::same_as<void>;
    
    // External copying
    { t.CopyBitsFrom(ct, start, count, dst) } -> std::same_as<void>;
    { ct.CopyBitsTo(t, start, count, dst) } -> std::same_as<void>;
    
    // Range operations
    { t.SetBitRange(start, count) } -> std::same_as<void>;
    { t.ClearBitRange(start, count) } -> std::same_as<void>;
    { t.FlipBitRange(start, count) } -> std::same_as<void>;
    
    // Validation
    { ct.CanCopyBits(ct, start, count, dst) } -> std::convertible_to<bool>;
};

#endif //BITCOPYABLE_H
