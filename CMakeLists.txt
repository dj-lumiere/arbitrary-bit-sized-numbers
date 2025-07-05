cmake_minimum_required(VERSION 3.13)
project(arbitrary_bitwidth_numbers)

enable_testing()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directory
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Concept headers
set(CONCEPT_HEADERS
        ${INCLUDE_DIR}/concepts/BitAccessible.h
        ${INCLUDE_DIR}/concepts/BitAnalyzable.h
        ${INCLUDE_DIR}/concepts/BitCopyable.h
        ${INCLUDE_DIR}/concepts/BitManipulable.h
        ${INCLUDE_DIR}/concepts/ByteAccessible.h
        ${INCLUDE_DIR}/concepts/ByteAnalyzable.h
        ${INCLUDE_DIR}/concepts/ByteCopyable.h
        ${INCLUDE_DIR}/concepts/ByteManipulable.h
        ${INCLUDE_DIR}/concepts/Storage.h
        ${INCLUDE_DIR}/concepts/MemoryPlace.h
)

# Core headers
set(CORE_HEADERS
        ${INCLUDE_DIR}/core/signed-int/ArbitrarySignedInt.h
        ${INCLUDE_DIR}/core/unsigned-int/ArbitraryUnsignedInt.h
        ${INCLUDE_DIR}/core/float/ArbitraryFloat.h
)

include_directories(include)

# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Create the main library
add_library(arbitrary_bitwidth_numbers INTERFACE ${CORE_HEADERS})

# Create test executable
add_executable(arbitrary_bitwidth_numbers_tests
        test/SignedIntTest.cpp
        test/UnsignedIntTest.cpp
        test/CPUStorageTest.cpp
        test/UnsignedIntTestWithOffset.cpp)

# Link the test executable with our library and Google Test
target_link_libraries(arbitrary_bitwidth_numbers_tests
        arbitrary_bitwidth_numbers
        gtest
        gtest_main)

# Register tests
include(GoogleTest)
gtest_discover_tests(arbitrary_bitwidth_numbers_tests)