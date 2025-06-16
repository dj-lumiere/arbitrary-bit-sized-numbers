//
// Created by Lumi on 25. 6. 16.
//

#ifndef IBYTEACCESSIBLE_H
#define IBYTEACCESSIBLE_H
#pragma once
#include <cstdint>

class IByteAccessible {
public:
    virtual ~IByteAccessible() = default;
    
    // Individual byte access
    virtual uint8_t& operator[](size_t index) = 0;
    virtual const uint8_t& operator[](size_t index) const = 0;
    virtual uint8_t* Data() = 0;
    virtual const uint8_t* Data() const = 0;
    
    // Size information
    virtual size_t GetByteSize() const = 0;
    
    // Bulk operations
    virtual void Fill(uint8_t value) = 0;
    virtual void Clear() = 0;
};

#endif //IBYTEACCESSIBLE_H
