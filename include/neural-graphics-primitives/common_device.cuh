/**
 * @file common_device.h
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
#include <neural-graphics-primitives/random_val.cuh>

#include <tiny-cuda-nn/common.h>
#include <tiny-cuda-nn/gpu_memory.h>

#include <Eigen/Dense>

RES_NAMESPACE_BEGIN

using precision_t = tcnn::network_precision_t;

// see https://zhuanlan.zhihu.com/p/66558476 for Gamma, sRGB and Linear Color
inline __host__ __device__ float srgb_to_linear(float srgb) {
    if (srgb <= 0.04045f) {
        return srgb / 12.92f;
    } else {
        return std::pow((srgb + 0.055f) / 1.055f, 2.4f);
    }
}

inline __host__ __device__ float linear_to_srgb(float linear) {
    if (linear < 0.0031308f) {
        return linear * 12.92f;
    } else {
        return 1.055f * std::pow(linear, 0.41666f) - 0.055f;
    }
}


// fetch the value of image in selected position 
template <uint32_t N_DIMS, typename T>
__host__ __device__ Eigen::Matrix<float, N_DIMS, 1> read_image(const T* __restrict__ data, const Eigen::Vector2i& resolution, const Eigen::Vector2f& pos) {
    const Eigen::Vector2f pos_float = Eigen::Vector2f{pos.x() * (float)(resolution.x() -1), pos.y() * (float)(resolution.y()-1)};
    const Eigen::Vector2i texel = pos_float.cast<int>();

    const Eigen::Vector2f weight = pos_float - texel.cast<float>();
    
    auto read_val = [&](Eigen::Vector2i pos) {
        pos.x() = std::max(std::min(pos.x(), resolution.x()-1), 0);
        pos.y() = std::max(std::min(pos.y(), resolution.y()-1), 0);

        Eigen::Matrix<float, N_DIMS, 1> result;
        if (std::is_same<T, float>::value) {
            result = *(Eigen::Matrix<T, N_DIMS, 1>*)&data[(pos.x()+pos.y() * resolution.x()) * N_DIMS];
        } else {
            auto val = *(tcnn::vector_t<T, N_DIMS>*)&data[(pos.x()+pos.y() * resolution.x()) * N_DIMS];

            RES_PRAGMA_UNROLL
            for (uint32_t i = 0; i < N_DIMS; ++i) {
                result[i] = (float)val[i]
            }
        }
        return result;
    }
    // averaging the fourt texel color around it using weight
    return (
        (1 - weight.x()) * (1 - weight.y()) * read_val({texel.x(), texel.y()}) + 
        (weight.x()) * (1 - weight.y()) * read_val({texel.x() + 1, texel.y()}) +
        (weight.x()) * (weight.y()) * read_val({texel.x() + 1, texel.y() + 1}) +
        (1 - weight.x()) * (weight.y()) * read_val({texel.x(), texel.y() + 1})
    );
}

