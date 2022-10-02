
// project
#include <neural-graphics-primitives/common.h>
// #include <neural-graphics-primitives/common_device.cuh>
#include <neural-graphics-primitives/testbed.h>

#include <tiny-cuda-nn/encodings/grid.h>
#include <tiny-cuda-nn/loss.h>
#include <tiny-cuda-nn/network_with_input_encoding.h>
#include <tiny-cuda-nn/network.h>
#include <tiny-cuda-nn/optimizer.h>
#include <tiny-cuda-nn/trainer.h>


#ifdef NGP_GUI
#   include <imgui/imgui.h>
#   include <imgui/backends/imgui_impl_glfw.h>
#   include <imgui/backends/imgui_impl_opengl3.h>
#   include <imguizmo/ImGuizmo.h>
#   include <stb_image/stb_image.h>
#   ifdef _WIN32
#       include <GL/gl3w.h>
#   else
#       include <GL/glew.h>
#   endif
#   include <GLFW/glfw3.h>
#endif

// Windows.h is evil, hahahaha
#undef min
#undef max
#undef near
#undef far

using namespace Eigen;
using namespace std::literals::chrono_literals;
using namespace tcnn;

NGP_NAMESPACE_BEGIN

bool Testbed::frame() {
#ifdef NGP_GUI
    // init window
    if (m_render_window) {
        if (!begin_frame_and_handle_user_input()) {
            return false;
        }
    }
#endif

    // Render against the trained neural network
    // we can skip rendering if the scene camera doesn't change
    // uint32_t n_to_skip = m_train ? tcnn::clamp(m_training_step / 16u, 15u, 255u) : 0;
    /*
    try {
        while (true) {
            // (*m_task_queue.tryPop())();
        }
    } catch (SharedQueueEmptyException&) {}
    */
    // train and render

#ifdef NGP_GUI 
    if (m_render_window) {
        if (m_gui_redraw) {
            // gather gui
        }
        // draw_gui()
        m_gui_redraw = false;
        m_last_gui_draw_time_point = std::chrono::steady_clock::now();
    }

    // ImGui::EndFrame
#endif 
    return true;
}

bool Testbed::begin_frame_and_handle_user_input() {
    bool ESCAPE_STATE = false;
    if (glfwWindowShouldClose(m_glfw_window) || ESCAPE_STATE) {
        destroy_window();
        return false;
    }

    {
        // update time
        auto now = std::chrono::steady_clock::now();
        auto elapsed = now - m_last_frame_time_point;
        m_last_frame_time_point = now;
        m_frame_ms.update(std::chrono::duration<float, std::milli>(elapsed).count());
    }

    glfwPollEvents();
    glfwGetFramebufferSize(m_glfw_window, &m_window_res.x(), &m_window_res.y());

    // IMGUI

    // NeRF special process

    // Keyboard Events
    // mouse_drag

    return true;
}

// merge_parent_network_config
// ends with
// load trining data

Testbed::Testbed(ETestbedMode mode)
: m_testbed_mode(mode)
{
    std::cout << "Testbed Init: " << std::endl;
}

Testbed::~Testbed() {
    // Destroy Window
}

void Testbed::init_window(int resw, int resh, bool hidden, bool second_window)
{
#ifndef NGP_GUI
	throw std::runtime_error{"init_window failed: NGP was built without GUI support"};
#else // define NGP_GUI
    std::cout << "Init Window" << std::endl; 
    // if not def NGP_GUI throw error
    m_window_res = { resw, resh };
    // glfw set error callback
    glfwSetErrorCallback(glfw_error_callback);
    // glfw init
    if (!glfwInit()) {
        throw std::runtime_error{"GLFW cound not be initialized."};
    }
// IF VULKAN SPECIAL
// ENDIF VULKAN

    // init GLFW Window Parameters
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, hidden ? GLFW_FALSE : GLFW_TRUE);
    std::string title = "SIRI: Neural Graphics Primitives (";
    switch (m_testbed_mode) {
        case ETestbedMode::Image: title += "Image"; break;
        case ETestbedMode::Nerf: title += "NeRf"; break;
        case ETestbedMode::Sdf: title += "SDF"; break;
        case ETestbedMode::Volume: title += "Volume"; break;
        default: title += "NOTITLE" ; break;
    }
    title += ")";
    // Create Window
    m_glfw_window = glfwCreateWindow(m_window_res.x(), m_window_res.y(), title.c_str(), NULL, NULL, NULL);
    if (m_glfw_window == NULL) {
        throw std::runtime_error("GLFW window could not be created");
    }
    glfwMakeContextCurrent(m_glfw_window);
#ifdef _WIN32
    if (gl3wInit()) {
        throw std::runtime_error("GL3W could not be initialized");
    }
#endif // _WIN32
    // OTHER DEBUGGING

    std::cout << "init window: " << title << std::endl;

    glfwSwapInterval(0); // Disable vsync
    // Set Window User Pointer
    glfwSetWindowUserPointer(m_glfw_window, this);
    
    // Set Drop Callback
    glfwSetDropCallback(m_glfw_window, [](GLFWwindow* window, int count, const char** path) {
        Testbed* testbed = (Testbed*)glfwGetWindowUserPointer(window);
        if (!testbed) {
            return;
        }
        //TODO testbed->redraw_gui_next_frame();
        for (int i = 0; i < count; i++) {
            // testbed->handle_file(paths[i])
        }
    })

    // Set Key Callback
    // Set Current PosCallback
    // Set ScrollCallback
    // Set WindowSize Callback
    glfwSetWindowSizeCallback(m_glfw_window, [](GLFWwindow* window, int width, int height) {
        Testbed* testbed = (Testbed*)glfwGetWindowUserPointer(window);
        if (testbed) {
            testbed->redraw_next_frame();
        }
    })
    // Set framebufferSizeCallback
    glfwSetFramebufferSizeCallback(m_glfw_window, [](GLFWwindow* window, int width, int height) {
        Testbed* testbed = (Testbed*)glfwGetWindowUserPointer(window);
        if (testbed) {
            testbed->redraw_next_frame();
        }
    })

    
    // scale seems no longer valid
    // float xscale, yscale;
    // glfwGetWindowContentScale(m_glfw_window, &xscale, &yscale);

    // IMGUI init

    // render texture
    //TODO: waiting for shared_queue and render_buffer 
    /*
    m_render_textures = { std::make_shared<GLTexture>() };
    m_render_surfaces.clear();
    m_render_surfaces.emplace_back(m_render_textures.front());
    m_pip_render_texture = std::make_shared<GLTexture>();
    m_pip_render_surface = std::make_unique<CudaRenderBuffer>(m_pip_render_texture);
    */
    // set render window 
    m_render_window = true;
    // second window
#endif // NGP_GUI
}

void Testbed::destroy_window() {
#ifndef NGP_GUI
    throw std::runtime_error("destroy window failed: NGP was built without GUI");
#else
    if (!m_render_window) {
        throw std::runtime_error("Window must be initialized before to be destroyed");
    }

    // m_render_surfaces.clear();
    // m_render_textures.clear();

    // m_pip_render_surface
    // m_pip_render_texture

    // dlss

    // IMGUI

    m_glfw_window = nullptr;
    m_render_window = false;
#endif // NGP_GUI
}




void glfw_error_callback(int error, const char* description) {
    // tlog::error 
}

NGP_NAMESPACE_END