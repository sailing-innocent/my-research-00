/**
 * @file: include/sail/cunn/common,h
 * @author: sailing-innocent
 * @create: 2022-10-25
 * @desp: The Common Definition for cuda nn library
*/
#pragma once 
#ifndef SAIL_CUNN_COMMON_H_
#define SAIL_CUNN_COMMON_H_

#include <sail/common.h>

#define SAIL_CUNN_NAMESPACE_BEGIN SAIL_NAMESPACE_BEGIN namespace cunn {
#define SAIL_CUNN_NAMESPACE_END SAIL_NAMESPACE_END }

#include <sail/cunn/cpp_api.h>

// fmt/core.h

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <cuda_fp16.h>

SAIL_CUNN_NAMESPACE_BEGIN

static constexpr uint32_t MIN_GPU_ARCH = 

SAIL_CUNN_NAMESPACE_END

#endif // SAIL_CUNN_COMMON_H_
