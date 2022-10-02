/**
 * @file render_buffer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <neural-graphics-primitives/common.h>
// #include <neural-graphics-primitives/common_device.cuh>
// #include <neural-graphics-primitives/dlss.h>

#include <tiny-cuda-nn/gpu-memory.h>

#include <memory>
#include <vector>

NGP_NAMESPACE_BEGIN

typedef unsigned int GLenum;
typedef int GLint;
typedef unsigned int GLuint;

class SurfaceProvider {
public:
    virtual cudaSurfaceObject_t surface() = 0;
    virtual cudaArray_t array() = 0;
    virtual Eigen::Vector2i resolution() const = 0;
    virtual void resize(const Eigen::Vector2i&) = 0;
};

class CudaSurface2D: public SurfaceProvider {};

class GLTexture: public SurfaceProvider {};

class CudaRenderBuffer {
public:
    CudaRenderBuffer(const std::shared_ptr<SurfaceProvider>& surf): m_surface_provider{surf} {}
    CudaRenderBuffer(const CudaRenderBuffer& other) = delete;
    CudaRenderBuffer(CudaRenderBuffer&& other) = default;

    Eigen::Vector2i in_resolution() const {
        return m_in_resolution;
    }

    Eigen::Vector2i out_resolution() const {
        return m_surface_provider->resolution;
    }

private:
    Eigen::Vector2i m_in_resolution = Eigen::Vector2i::Zero();

    tcnn::GPUMemory<Eigen::Array4f> m_frame_buffer;
    tcnn::GPUMemory<float> m_depth_buffer;
    tcnn::GPUMemory<Eigen::Array4f> m_accumulate_buffer;

    std::shared_ptr<SurfaceProvider> m_surface_provider;
};

NGP_NAMESPACE_END