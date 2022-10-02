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

// TOOLS
// adam_optimizer
// camera_path
// common
// discrete_distribution
// nerf
// nerf_loader
// render_buffer
// sdf
// share_queue
// trainable_buffer

// DEPS
// cuda_graph
// random

// json
// path
// pybind
// thread

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

NGP_NAMESPACE_BEGIN

template <typename T> class NerfNetwork;
class TriangleOctree;
class TriangleBvh;
struct Triangle;
class GLTexture;

class Testbed {
public:
    Testbed(ETestbedMode mode);
    ~Testbed();
    void init_window(int resw, int resh, bool hidden, bool second_window);
    void destroy_window();
    bool frame();
        bool begin_frame_and_handle_user_input();
private:
    // Basic Window
    ETestbedMode m_testbed_mode = ETestbedMode::Nerf;
    Eigen::Vector2i m_window_res = Eigen::Vector2i::Constant(0);
    GLFWwindow* m_glfw_window = nullptr;
    bool m_render_window = false;
    std::chrono::time_point<std::chrono::steady_clock> m_last_frame_time_point;
    
    

private:
    // GUI
    bool m_gui_render = false;
    std::chrono::time_point<std::chrono::steady_clock> m_last_gui_draw_time_point;
    bool m_gui_redraw = false; // REDRAW THE GUI CONTENT
    
private:
    // Rendering/UI bookkeeping
    Ema m_training_ms = {EEmaType::Time, 100};
    Ema m_render_ms = {EEmaType::Time, 100};
    Ema m_frame_ms = {EEmaType::Time, 100};

};

void glfw_error_callback(int error, const char* description);

NGP_NAMESPACE_END
