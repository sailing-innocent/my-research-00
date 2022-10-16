cmake_minimum_required(VERSION 3.18)

project(
    sail-nn
    VERSION 0.1
    DESCRIPTION "MY Learning NN lib for tiny-cuda-nn"
    LANGUAGES CXX CUDA
)

option(SAIL_NN_BUILD_BENCHMARK "Build SAIL_NN BENCHMARK?" ON)
option(SAIL_BUILD_EXAMPLES "Build sail-nn example applications?" ON)
set(SAIL_NN_CUDA_ARCHITECTURES "" CACHE STRING "Build SAIL-NN for specific CUDA GPU Architecture.")

##################################################################################################
# Build Type and C++ Compiler
##################################################################################################

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No releases type specified. Setting to 'Release'. ")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif()

# IF_APPLE

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


##################################################################################################
# CUDA Compiler
##################################################################################################

set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS OFF)
set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)

get_directory_property(SAILNN_HAS_PARENT PARENT_DIRECTORY)

