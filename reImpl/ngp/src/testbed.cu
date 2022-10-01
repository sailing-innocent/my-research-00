
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

Testbed::Testbed(ETestbedMode mode)
: m_testbed_mode(mode)
{
    // config
}

Testbed::~Testbed() {
    // Destroy Window
}

void Testbed::init_window(int resw, int resh, bool hidden, bool second_window)
{
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
    }
    title += ")";
    
    // Create Window
    // m_glfw_window = glfwCreateWindow(m_window_res.x(), m_window_res.y(), title.c_str(), NULL, NULL);
    if (m_glfw_window == NULL) {
        throw std::runtime_error("GLFW window could not be created");
    }
    // OTHER DEBUGGING

    std::cout << "init window: " << title << std::endl;

    glfwSwapInterval(0); // Disable vsync

}

void glfw_error_callback(int error, const char* description) {
    // tlog::error 
}

NGP_NAMESPACE_END