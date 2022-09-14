# Notes for Research

This is my notes during the research, I am a pare newbie for this region so I have to learn every details

## Progress

- 2022-09-14 终于看懂了项目的框架和各个部分的功能。cmake用得也开始熟练了。后面半个月的时间的任务就两个，一个是不断学习和扩展相关的能力，一个是用这个框架不断阅读和复现其他研究的代码
- 

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

### Main Build Process

- `testbed.load_training_data(scene_path.str());`
- `testbed.init_window(width_flag ?get(width_flag) :1920, height_flag ?get(height_flag) :1080);`
- train

```cpp
		// Render/training loop
		while (testbed.frame()) {
			if (!gui) {
				tlog::info() << "iteration=" << testbed.m_training_step << " loss=" << testbed.m_loss_scalar.val();
			}
		}
```
