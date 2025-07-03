//
// Created by Lumi on 25. 7. 2.
//

#ifndef STORAGE_H
#define STORAGE_H

#include "BitAccessible.h"
#include "BitAnalyzable.h"
#include "BitCopyable.h"
#include "BitManipulable.h"
#include "ByteAccessible.h"
#include "ByteAnalyzable.h"
#include "ByteCopyable.h"
#include "ByteManipulable.h"
#include <concepts>
#include <memory>

template<typename T, size_t size>
concept Storage = BitAccessible<T> && BitAnalyzable<T> && BitCopyable<T> && 
                  BitManipulable<T> && ByteAccessible<T> && ByteAnalyzable<T> && 
                  ByteCopyable<T> && ByteManipulable<T> && requires(T ct) {
    // Clone functionality
    { ct.Clone() } -> std::same_as<std::unique_ptr<T>>;
    
    // Size information
    { ct.GetByteSize() } -> std::same_as<size_t>;
    
    // Requirement that size matches
    requires ct.GetByteSize() == size;
};

#endif //STORAGE_H