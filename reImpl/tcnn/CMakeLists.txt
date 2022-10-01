cmake_minimum_required(VERSION 3.10)

project(
    tiny-cuda-nn
    VERSION 1.6
    DESCRIPTION "The Reimplementation of Tiny CUDA NN"
    LANGUAGES CXX CUDA
)

option(TCNN_BUILD_BENCH_MARK "Build TCNN example benchmark" ON)
option(TCNN_BUILD_EXAMPLES "Build TCNN example applicators?" ON)
set(TCNN_CUDA_ARCHITECTURES "" CACHE STRING "Build TCNN for a specified CUDA Architecture")

# Build type and C++ compiler setup

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No release type specified, Setting to 'Release' ")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif()

# CMAKE CURRENT SOURCE DIR

# IF APPLE

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CUDA Environment setup

set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS OFF)
set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)

get_directory_property(TCNN_HAS_PARENT PARENT_DIRECTORY)

# TODO: ADAPTIVELY SET
set(CMAKE_CUDA_ARCHITECTURES 86)

# Remove unsupported architectures
# Remove duplicated

# CUDA VERSION
message(STATUS "Targeting GPU architectures: ${CMAKE_CUDA_ARCHITECTURES}")

list(APPEND CUDA_NVCC_FLAGS "--extended-lambda")
list(APPEND CUDA_NVCC_FLAGS "--expt-relaxed-constexpr")

# Dependencies

find_library(
    CUDA_CUBLASLT_LIBRARY cublasLt
    ${CUDA_TOOLKIT_ROOT_DIR}/lib64
    ${CUDA_TOOLKIT_ROOT_DIR}/lib
)

set(BUILD_SHARED_LIBS OFF)
# add_subdirectory("dependencies/fmt")

# TCNN library, samples and benchmarks

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})

set(TCNN_SOURCES
    # src/common.cu
    # src/common_device.cu
    # cpp_api
    # cutlass_mlp
    # encoding
    # loss
    # network
    # object
    # optimizer
    # reduce_sum
)

add_library(tiny-cuda-nn STATIC ${TCNN_SOURCES})
target_compile_definitions(tiny-cuda-nn PUBLIC ${TCNN_DEFINITIONS})
target_compile_options(tiny-cuda-nn PUBLIC $<$<COMPILE_LANGUAGE:CUDA>:${CUDA_NVCC_FLAGS}>)
target_include_directories(tiny-cuda-nn PUBLIC
    # "include"
    # "dependencies"
    # "dependencies/cutlass/include"
    # "dependencies/cutlass/util/include"
    # "dependencies/fmt/include"
)
target_link_libraries(tiny-cuda-nn PUBLIC ${CUDA_LIBRARIES} cuda culblas fmt)

if (TCNN_BUILD_EXAMPLES)
    add_subdirectory("samples")
endif()

if (TCNN_BUILD_BENCHMARK)
    add_subdirectory("benchmarks/image")
endif()
