/**
 * @file bounding_box.cuh
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
#include <neural-graphics-primitives/common-device.cuh>
#include <neural-graphics-primitives/triangle.cuh>

RES_NAMESPACE_BEGIN

struct BoundingBox {
    RES_HOST_DEVICE BoundingBox() {}

    RES_HOST_DEVICE BoundingBox(const Eigen::Vector3f& a, const Eigen::Vector3f& b) : min{a}, max{b} {}

    Eigen::Vector3f min = Eigen::Vector3f::Constant(std::numeric_limits<float>::infinity());
    Eigen::Vector3f max = Eigen::Vector3f::Constant(-std::numeric_limits<float>::infinity());
};

inline std::ostream& operator<<(std::ostream& os, const res::BoundingBox& bb) {
    os << "[";
    os << "min=[" << bb.min.x() << "," << bb.min.y() << "," << bb.min.z() << "],";
    os << "max=[" << bb.max.x() << "," << bb.max.y() << "," << bb.max.z() << "]";
    os << "]";
    return os;
}

RES_NAMESPACE_END