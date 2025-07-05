# Arbitrary Bit Width Numbers

## Warning: This library is in development stage!

A C++ library providing backend-agnostic arbitrary-precision arithmetic types with customizable bit widths and storage backends.

## Features

### 🔢 Arbitrary Precision Integer Types
- **ArbitrarySignedInt**: Two's complement signed integers with arbitrary bit width
- **ArbitraryUnsignedInt**: Unsigned integers with arbitrary bit width
- Full arithmetic operations with overflow handling
- Bit manipulation and analysis functions
- Conversion to/from standard integer types

### 🔴 Arbitrary Precision Floating Point
- **ArbitraryFloat**: IEEE 754 compliant floating point with customizable exponent and mantissa sizes
- Support for special values (NaN, Infinity, subnormal numbers)
- Mathematical functions (trigonometric, logarithmic, exponential)
- Rounding modes and precision control
- Conversion between different floating point formats

### 🏗️ Backend Agnostic Storage
- **CPUStorage**: High-performance CPU-based storage backend
- Interface-based design allows custom storage implementations
- Support for different memory architectures (GPU, FPGA, etc.)
- Efficient bit and byte manipulation operations

## Quick Start

### Basic Usage

```c++
#include "ArbitrarySignedInt.h"
#include "ArbitraryUnsignedInt.h"
#include "ArbitraryFloat.h"
#include "storage/CPUStorage.h"

// 128-bit signed integer using CPU storage
using Int128 = ArbitrarySignedInt<128, 0, CPUMemoryPlace>;
Int128 a = 1234567890;
Int128 b = -987654321;
Int128 result = a + b;

// 256-bit unsigned integer
using UInt256 = ArbitraryUnsignedInt<256, 0, CPUMemoryPlace>;
UInt256 large = UInt256::FromString("123456789012345678901234567890");

// Custom floating point: 11-bit exponent, 52-bit mantissa (like double)
using Float64 = ArbitraryFloat<11, 52, CPUMemoryPlace>;
Float64 x = 3.14159;
Float64 y = Float64::Sin(x);
```


### Custom Bit Widths

```c++
// 24-bit signed integer
using Int24 = ArbitrarySignedInt<24, 0, CPUMemoryPlace>;

// 10-bit floating point (5-bit exponent, 4-bit mantissa)
using Float10 = ArbitraryFloat<5, 4, CPUMemoryPlace>;

// Very high precision: 15-bit exponent, 112-bit mantissa
using QuadFloat = ArbitraryFloat<15, 112, CPUMemoryPlace>;
```


## Architecture

### Concept Hierarchy

The library is built on a modular concept system:

- **ByteAccessible**: Basic byte-level access
- **BitAccessible**: Bit-level manipulation
- **ByteAnalyzable**: Byte pattern analysis
- **BitAnalyzable**: Bit counting and pattern detection
- **Storage**: Combined storage interface

### Storage Backends

Currently implemented:
- **CPUStorage**: Optimized for CPU operations
- Extensible to custom backends (GPU, network, persistent storage, etc.)

## Building

```shell script
mkdir build
cd build
cmake ..
make
```


### Requirements
- C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 2019+)
- CMake 3.15+

## Features in Detail

### Integer Operations
- All standard arithmetic operators (`+`, `-`, `*`, `/`, `%`)
- Bitwise operations (`&`, `|`, `^`, `~`, `<<`, `>>`)
- Comparison operators with proper two's complement handling
- Bit manipulation functions (count leading/trailing zeros, population count)
- String conversion (binary, decimal, hexadecimal)

### Floating Point Operations
- IEEE 754 compliant arithmetic
- Special value handling (NaN, Infinity, subnormal)
- Mathematical functions (sin, cos, log, exp, sqrt, etc.)
- Multiple rounding modes
- Format conversion between different precisions

### Advanced Features
- Checked arithmetic with overflow detection
- Fused multiply-add operations
- Next representable value functions
- Bit-exact serialization/deserialization
- Thread-safe operations

## Examples

### High-Precision Calculations

```c++
// Calculate π with 256-bit precision
using HighPrecFloat = ArbitraryFloat<19, 236, CPUMemoryPlace>;
HighPrecFloat pi = HighPrecFloat::Pi();
HighPrecFloat result = HighPrecFloat::Sin(pi / 6); // Should be 0.5
```


### Cryptographic Integers

```c++
// 2048-bit integer for RSA operations
using RSAInt = ArbitraryUnsignedInt<2048, 0, CPUMemoryPlace>;
RSAInt p = RSAInt::GeneratePrime(); // Hypothetical prime generation
RSAInt q = RSAInt::GeneratePrime();
RSAInt n = p * q;
```


### Embedded Fixed-Point

```c++
// 16-bit fixed point with 8 fractional bits
using Fixed16_8 = ArbitrarySignedInt<16, 0, CPUMemoryPlace>;
// Manual fixed-point arithmetic
Fixed16_8 a = 256; // Represents 1.0
Fixed16_8 b = 128; // Represents 0.5
Fixed16_8 sum = a + b; // Represents 1.5
```


## Contributing

1. Fork the repository
2. Create a feature branch
3. Add tests for new functionality
4. Ensure all tests pass
5. Submit a pull request

## License

MIT License

## Roadmap

- [ ] GPU storage backend (CUDA/OpenCL)
- [ ] SIMD optimizations for large integers
- [ ] Decimal floating point support
- [ ] Python bindings
- [ ] Performance benchmarking suite
- [ ] Extended mathematical function library
- [ ] Make it into C++ module
