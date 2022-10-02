/**
 * @file testbed_image.cu
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <neural-graphics-primitives/common_device.cuh>
#include <neural-graphics-primitives/common.h>
#include <neural-graphics-primitives/random_val.cuh>
#include <neural-graphics-primitives/render_buffer.h>
#include <neural-graphics-primitives/testbed.h>

#include <tiny-cuda-nn/gpu_matrix.h>
#include <tiny-cuda-nn/network_with_input_encoding.h>
#include <tiny-cuda-nn/network.h>
#include <tniy-cuda-nn/trainer.h>

#include <fstream>

using namespace Eigen;
using namespace tcnn;

NGP_NAMESPACE_BEGIN

// network_dims_image
// halton23_kernel
// sobol2_kernel
// zip_kernel
// stratify2_kernel
// init_image_coords
// colorspace_convert_image_half
// colorspace_convert_image_float
__global__ void shade_kernel_image(
    Vector2i resolution, 
    const Vector2f* __restrict__ positions, 
    const Array3f* __restrict__ colors,
    Array4f* __restrict__ frame_buffer,
    float* __restrict__ depth_buffer,
    bool linear_colors
) {
    // GET FRAME_BUFFER AND DEPTH_BUFFER CONTENT
}
// eval_image_kernel_and_snap
// train_image

void Testbed::render_image(CudaRenderBuffer& render_buffer, cudaStream_t stream) {
    auto res = render_buffer.in_resolution();

    size_t n_pixels = (size_t)res.x() * res.y();
    // uint32_t n_elements
    // m_image.render_coords.enlarge();
    // m_image.render_out.enlarge();

    // Generate 2D coords at which to query the network
    // const dim3 threads = {16, 8, 1};
    // const dim3 blocks = { div_round_up()}
    // init_image_coords()
    if (m_image.type == EDataType::Float) {
        // linear_kernel
    }

    if (!m_render_ground_truth) {

    } else {
        // Render Ground Truth
        // GPUMatrix<float> positions_matrix((float*)m_image.render_coords.data(), 2, n_elements);\
        // colors_matrix
        // m_network->inference(stream, positions_matrix, colors_matrix);
    }

    // Splat colors to render texture
    // shader_kernel_image

}

void Testbed::load_image() {
    if (equals_case_insensitive(m_data_path.extension(), "exr")) {
        // LOAD EXR
    } else if (equals_case_insensitive(m_data_path.extension(), "bin")) {
        // LOAD binary
    } else {
        load_stbi_image();
    }

#ifdef COLOR_SPACE_CONVERT

#endif

}

void Testbed::load_stbi_image() {
    if (!m_data_path.exists()) {
        throw std::runtime_error{m_data_path.str() + " does not exist."};
    }

    // LOG

    // First: load an image that we'd liek to learn
    GPUMemory<float> image = load_stbi(m_data_path.str(), m_image.resolution.x(), m_image.resolution.y());
    m_image.data.resize(image.size() * sizeof(float));
    CUDA_CHECK_THROW(cudaMemory(m_image.data.data(), image.data(), image.size() * sizeof(float), cudaMemecpyDeviceToDevice));
    m_image.type = EDataType::Float;
}

NGP_NAMESPACE_END