cmake_minimum_required(VERSION 3.13)
project(arbitrary_bitwidth_numbers)

enable_testing()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directory
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Interface headers
set(INTERFACE_HEADERS
        ${INCLUDE_DIR}/interfaces/IBitAccessible.h
        ${INCLUDE_DIR}/interfaces/IBitAnalyzable.h
        ${INCLUDE_DIR}/interfaces/IBitCopyable.h
        ${INCLUDE_DIR}/interfaces/IBitManipulable.h
        ${INCLUDE_DIR}/interfaces/IByteAccessible.h
        ${INCLUDE_DIR}/interfaces/IByteAnalyzable.h
        ${INCLUDE_DIR}/interfaces/IByteCopyable.h
        ${INCLUDE_DIR}/interfaces/IByteManipulable.h
        ${INCLUDE_DIR}/interfaces/IStorage.h
        include/interfaces/IBitManipulable.h
)

# Core headers
set(CORE_HEADERS
        ${INCLUDE_DIR}/ArbitrarySignedInt.h
        ${INCLUDE_DIR}/ArbitraryUnsignedInt.h
        ${INCLUDE_DIR}/ArbitraryFloat.h
)

include_directories(include)

# Create the main library
add_library(arbitrary_bitwidth_numbers INTERFACE ${CORE_SOURCES} ${INTERFACE_HEADERS} ${CORE_HEADERS})

# Create test executable
add_executable(arbitrary_bitwidth_numbers_tests test/signedinttest.cpp)
target_link_libraries(arbitrary_bitwidth_numbers_tests arbitrary_bitwidth_numbers)

# Add test to CTest
add_test(NAME SignedIntTest COMMAND signed_int_test)

# Optional: Create an example/demo executable if you have a main.cpp
# add_executable(lumi_math_demo src/main.cpp)
# target_link_libraries(lumi_math_demo arbitrary_bitwidth_numbers)
