//
// Created by Lumi on 25. 7. 2.
//

#ifndef STORAGE_PROVIDER_H
#define STORAGE_PROVIDER_H

#include "Storage.h"
#include <concepts>

template<typename T, size_t size>
concept StorageProvider = requires {
    // Check that the StorageType alias exists
    typename T::template StorageType<size>;
    
    // Check that the StorageType satisfies Storage concept
    requires Storage<typename T::template StorageType<size>, size>;
    
    // Check that create() returns the correct type
    { T::template create<size>() } -> std::same_as<typename T::template StorageType<size>>;
};

#endif //STORAGE_PROVIDER_H
