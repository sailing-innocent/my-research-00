/**
 * @file triangle.cuh
 * @author your name (you@domain.com)
 * @brief CUDA/C++ triangle implementation
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once 

#include <neural-graphics-primitives/common.h>
#include <neural-graphics-primitives/common_device.cuh>

#include <tiny-cuda-nn/common.h>

RES_NAMESPACE_BEGIN

struct Triangle {
    RES_HOST_DEVICE Eigen::Vector3f sample_uniform_position(const Eigen::Vector2f& sample) const {
        float sqrt_x = std::sqrt(sample.x());
        float factor0 = 1.0f - sqrt_x;
        float factor1 = sqrt_x * ( 1.0f - sample.y());
        float factor2 = sqrt_x * sample.y();

        return  factor0 * a + factor1 * b + factor2 * c;
    }

    Eigen::Vector3f a, b, c;
};

inline std::ostream& operator<<(std::ostream& os, const res::Triangle& triangle) {
    os << "[";
    os << "a=[" << triangle.a.x() << "," << triangle.a.y() << "," << triangle.a.z() << "], ";
    os << "b=[" << triangle.b.x() << "," << triangle.b.y() << "," << triangle.b.z() << "], ";
    os << "c=[" << triangle.c.x() << "," << triangle.c.y() << "," << triangle.c.z() << "]";
    os << "]";
    return os;
}

RES_NAMESPACE_END
