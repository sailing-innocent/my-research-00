#pragma once

#include <tinylogger/tinylogger.h>

#if defined(__NVCC__)
#define RES_HOST_DEVICE __host __device__
#else
#define RES_HOST_DEVICE
#endif

inline RES_HOST_DEVICE float sign(float x) {
    return copysignf(1.0, x);
}

inline RES_HOST_DEVICE uint32_t binary_search(float val, const float* data, uint32_t length) {
    if (length == 0) {
        return 0;
    }

    uint32_t it;
    uint32_t count, step;
    count = length;

    uint32_t first = 0;
    while (count > 0) {
        it = first;
        step = count / 2;
        it += step;
        if (data[it] < val) {
            first = ++it;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    return std::min(first, length - 1);
}

#include <Eigen/Dense>

#define RES_NAMESPACE_BEGIN namespace res {
#define RES_NAMESPACE_END }

#if defined(__CUDA_ARCH__)
    #if defined(_CUDACC_RTC__) || (defined(__clang__) && defined(__CUDA__))
        #define RES_PRAGMA_UNROLL _Pragma("unroll")
        #define RES_PRAGMA_NO_UNROLL _Pragma("unroll 1")
    #else
        #define RES_PRAGMA_UNROLL #pragma unroll
        #define RES_PRAGMA_NO_UNROLL #pragma unroll 1
    #endif
#else
    #define RES_PRAGMA_UNROLL
    #define RES_PRAGMA_NO_UNROLL
#endif

#include <chrono>
#include <functional>

RES_NAMESPACE_BEGIN

using Vector2i32 = Eigen::Matrix<uint32_t, 2, 1>;
using Vector3i16 = Eigen::Matrix<uint16_t, 3, 1>;
using Vector4i16 = Eigen::Matrix<uint16_t, 4, 1>;
using Vector4i32 = Eigen::Matrix<uint32_t, 4, 1>;

enum class EMeshRenderMode : int {
    Off,
    VectorColors,
    VectorNormals,
    FaceIDs,
};

enum class ERenderMode : int {
    AO,
    Shade,
    Normals,
    Positions,
    Depth,
    Distortion,
    Cost,
    Slice,
    NumRenderModes,
    EncodingVis,
};