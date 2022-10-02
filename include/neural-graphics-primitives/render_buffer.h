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
#include <neural-graphics-primitives/common_device.cuh>
// #include <neural-graphics-primitives/dlss.h>

#include <tiny-cuda-nn/gpu-memory.h>

#include <memory>
#include <vector>

NGP_NAMESPACE_BEGIN

typedef unsigned int GLenum;
typedef int          GLint;
typedef unsigned int GLuint;

class SurfaceProvider {
public:
    virtual cudaSurfaceObject_t surface() = 0;
    virtual cudaArray_t array() = 0;
    virtual Eigen::Vector2i resolution() const = 0;
    virtual void resize(const Eigen::Vector2i&) = 0;
};

class CudaSurface2D: public SurfaceProvider {
public:
    CudaSurface2D() {
        m_array = nullptr;
        m_surface = 0;
    }
    ~CudaSurface2D() {
        free();
    }

    void free();
    void resize(const Eigen::Vector2i& size) override;

    cudaSurfaceObject_t surface() override {
        return m_surface;
    }

    cudaArray_t array() override {
        return m_size;
    }
private:
    Eigen::Vector2i m_size = Eigen::Vector2i::Constant(0);
    cudaArray_t m_array;
    cudaSurfaceObject_t m_surface;
};

//ifdef NGP_GUI
class GLTexture: public SurfaceProvider {
public:
    GLTexture() = default;
    GLTexture(const std::string& texture_name): m_texture_name(texture_name), m_texture_id(0)
    {}

    GLTexture(const GLTexture& other) = delete;
    GLTexture(GLTexture&& other)
    : m_texture_name(move(other.m_texture_name)), m_texture_id(other.m_texture_id) {
        other.m_texture_id = 0;
    }

    GLTexture& operator=(GLTexture&& other) {
        m_texture_name = move(other.m_texture_name);
        std::swap(m_texture_id, otehr.m_texture_id);
        return *this;
    }

    ~GLTexture();

    GLuint texture();

    cudaSurfaceObject_t surface() override;

    cudaArray_t array() override;

    void blit_from_cuda_mapping();

    const std::string& texture_name() const { return m_texture_name; }
private:
    class CUDAMapping {

    };

    std::string m_texture_name;
    GLuint m_texture_id = 0;
    Eigen::Vector2i m_size = Eigen::Vector2i::Constant(0);
    int m_n_channels = 0;
    GLint m_internal_format;
    GLenum m_format;
    bool m_is_8bit = false;
    std::unique_ptr<CUDAMapping> m_cuda_mapping;
};

#endif // NGP_GUI


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

    void resize(const Eigen::Vector2i& res);

    void reset_accumulation() {
        m_spp = 0;
    }

    uint32_t spp() const {
        return m_spp;
    }

    Eigen::Array4f* frame_buffer() const {
        return m_frame_buffer.date();
    }

    float* depth_buffer() const {
        return m_depth_buffer.data();
    }

    Eigen::Array4f* accumulate_buffer() const {
        return m_accumulate_buffer.data();
    }
    void clear_frame(cudaStream_t stream);

    void accumulate(float exposure, cudaStream_t stream);

    void tonemap(float exposure, const Eigen::Array4f& background_color, EColorSpace output_color, cudaStream_t stream);

    // void overlay_image();
private:
    Eigen::Vector2i m_in_resolution = Eigen::Vector2i::Zero();

    tcnn::GPUMemory<Eigen::Array4f> m_frame_buffer;
    tcnn::GPUMemory<float> m_depth_buffer;
    tcnn::GPUMemory<Eigen::Array4f> m_accumulate_buffer;

    std::shared_ptr<SurfaceProvider> m_surface_provider;
};

NGP_NAMESPACE_END