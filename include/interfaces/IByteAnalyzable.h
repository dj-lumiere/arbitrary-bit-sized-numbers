//
// Created by Lumi on 25. 6. 16.
//

#ifndef IBYTEANALYZABLE_H
#define IBYTEANALYZABLE_H
#include <cstdint>
#include <optional>
#include <span>

class IByteAnalyzable {
public:
    virtual ~IByteAnalyzable() = default;
    
    // Pattern searching
    virtual std::optional<size_t> FindByte(uint8_t value, size_t startPos = 0) const = 0;
    virtual std::optional<size_t> FindBytePattern(std::span<const uint8_t> pattern, size_t startPos = 0) const = 0;
    
    // Comparison
    virtual int Compare(const IByteAnalyzable& other) const = 0;
    virtual int Compare(std::span<const uint8_t> data) const = 0;
    virtual bool Equal(const IByteAnalyzable& other) const = 0;
    virtual bool Equal(std::span<const uint8_t> data) const = 0;
    
    // Checksums
    virtual uint32_t ComputeCRC32() const = 0;
    virtual uint64_t ComputeHash() const = 0;
};

#endif //IBYTEANALYZABLE_H
