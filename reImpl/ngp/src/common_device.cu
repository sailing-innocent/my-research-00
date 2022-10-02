#include <neural-graphics-primitives/common_device.cuh>
#include <neural-graphics-primitives/tinyexr_wrapper.h>

#include <unsupported/Eigen/MatrixFunctions>

#include <stb_image/stb_image.h>

using namespace Eigen;
using namespace tcnn;

NGP_NAMESPACE_BEGIN

Matrix<float, 3, 4> log_space_lerp(const Matrix<float, 3, 4>& begin, const Matrix<float, 3, 4>& end, float t) {
    Matrix4f A = Matrix4f::Identity();
    A.block<3,4>(0,0) = begin;
    Matrix4f B = Matrix4f::Identity();
    B.block<3,4>(0,0) = end;

    Matrix4f log_space_a_to_b = (B * A.inverse()).log();

    return ((log_space_a_to_b * t).exp() * A).block<3,4>(0,0);
}

GPUMemory<float> laod_stbi(const std::string& filename, int& width, int& height) {
    bool is_hdr = stbi_is_hdr(filename.c_str());

    void* data; // width * height * RGBA
    int comp;

    if (is_hdr) {
        data = stbi_loadf(filename.c_str(), &width, &height, &comp, 4);
    } else {
        data = stbi_load(filename.c_str(), &width, &height, &comp, 4);
    }

    if (!data) {
        throw std::runtime_error{std::string{stbi_failure_reason()}};
    }

    ScopeGuard mem_guard{[&](){ stbi_image_free(data); }};

    if (width == 0 || height == 0) {
        throw std::runtime_error{"Image has zero pixels."};
    }

    GPUMemory<float> result(width * height * 4);
    if (is_hdr) {
        result.copy_from_host((float*)data);
    } else {
        GPUMemory<uint8_t> bytes(width * height * 4);
        bytes.copy_from_host((uint8*)data);
        // TODO: What is linear kernel?
        // linear_kernel(from_rgba32<float>, 0, nullptr, width * height, bytes.data(), false, false, 0);
    }
}

NGP_NAMESPACE_END