/**
 * @file testbed.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

struct GLFWwindow;

#include <neural-graphics-primitives/common.h>

#include <tiny-cuda-nn/cuda_graph.h>
#include <tiny-cuda-nn/random.h>

TCNN_NAMESPACE_BEGIN
template <typename T> class Loss;
template <typename T> class Optimizer;
template <typename T> class Encoding;
template <typename T, typename PARAMS_T> class Network;
template <typename T, typename PARAMS_T, typename COMPUTE_T> class Trainer;
template <uint32_t N_DIMS, uint32_t RANK, typename T> class TrainableBuffer;
TCNN_NAMESPACE_END

RES_NAMESPACE_BEGIN

template <typename T> class NerfNetwork;
class TriangleOctree;
class TriangleBvh;
struct Triangle;
class GLTexture;

class Testbed {
public:
    Testbed();
    ~Testbed();
    void load_training_data(const std::string& data_path);
    void clear_training_data();

    using distance_fun_t = std::function<void(uint32_t, const tcnn::GPUMemory<Eigen::Vector3f>&, tcnn::GPUMemory<float>&, cudaStream_t)>;

    class SphereTracer {
    public:
        SphereTracer(): m_hit_counter(1), m_alive_counter(1) {}

        void init_rays_from_camera(
            uint32_t spp,
        );
        // void init_rays_from_data(uint32_t n_elements, const RaysSdfSoa& data)
        uint32_t trace_bvh();
        uint32_t trace();
        void enlarge(size_t n_elements);

    private:
        uint32_t m_n_rays_initialized = 0;
    };

    class NerfTracer {};

    class FiniteDifferenceNormalsApproximator {};

    struct NetworkDims {
        uint32_t n_input;
        uint32_t n_output;
        uint32_t n_pos;
    };

    NetworkDims network_dims_volume() const;
    NetworkDims network_dims_nerf() const;

    void render_volume();
    void train_volume();
    void training_prep_volume()
    void load_volume();

    void render_nerf();
    void render_image();
    void render_frame();

    void reload_network_from_file()

    void reset_network();
    void create_empty_nerf_dataset();
    void load_nerf();
    void load_nerf_post();
}

RES_NAMESPACE_END