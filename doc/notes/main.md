# Notes for Research

This is my notes during the research, I am a pare newbie for this region so I have to learn every details

## Preparation

- An **NVIDIA GPU**
- A **C++ 14** capable library
  - Windows: Visual Studio 2019
- CUDA v10.2 or higher
- CMake v3.21 or higher
- Python, OptiX, Vulkan

### Learn Dependencies

- pybind11
- eigen
- glfw
- args
- tinylogger
- tiny-cuda-nn
- imgui
- DLSS

其中核心的计算库是eigen和tiny-cuda-nn，而imgui, glfw, DLSS是可视化界面的库，pybind11是python接口的库，而tinylogger, args是帮助库。
