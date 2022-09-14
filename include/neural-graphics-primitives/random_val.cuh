/**
 * @file random_val.cuh
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <neural-graphics-primitives/common.h>
#include <tiny-cuda-nn/random.h>
#include <Eigen/Dense>

RES_NAMESPACE_BEGIN

using default_rng_t = tcnn::default_rng_t;

inline constexpr float PI() { return 3.14159265358979323846f; }

template <typename RNG>
inline __host__ __device__ float randome_val(RNG& rng) {
    return rng.next_float();
}

template <template RNG>
inline __host__ __device__ uint32_t random_uint(RNG& rng) {
    return rng.next_uint();
}

RES_NAMESPACE_END
