# Dependencies.Pybind11

[Tom94/pybind11: Seamless operability between C++11 and Python (github.com)](https://github.com/Tom94/pybind11)

Seamless operability between C++11 and Python

- a lightweight header-only library that exposes C++ types in Python and vice versa

## Installation

You can use pybind11 repository as a submodule

`git submodule add -b stable https://github.com/Tom94/pybind11 dependencies/pybind11`

now you can find them in "dependencies/pybind11" directory

## Hello World

This hello world project is somewhat different. We can devide it into 2 steps:

- compile the example.cc file to generate example.pyd dynamic library file for python
- create test.py to use example.pyd to execute add() function defined in it (which is written in C++)

### Library Compilation

create an empty directory called example, and place example.cc

```cc
#include <pybind11/pybind11.h>

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin";
    m.def("add", &add, "A function that adds two numbers.");
}


```

and CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.4)

project(bindPY)
if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP24")
endif()

include_directories("../../../dependencies/pybind11/include")
include_directories("E:/env/python/include")
find_package(Python 3.7 COMPONENTS Interpreter Development)

if (Python_FOUND)
    add_subdirectory("../../../dependencies/pybind11" "./pybind_dep")
    add_library(example SHARED example.cc)
	set_target_properties(example PROPERTIES CXX_VISIBILITY_PRESET "hidden" CUDA_VISIBILITY_PRESET "hidden")
	target_link_libraries(example PUBLIC ${PYTHON_LIBRARIES} pybind11::module)
	target_compile_definitions(example PUBLIC -DNGP_PYTHON)
	pybind11_extension(example)
endif()


```

our CMakeLists.txt file is self-explained, we will add include directory <path/to/dependencies/pybind11/include> to let compiler know where to find <pybind11/pybind11.h> amd add <path/to/python/include> to let compiler know where to find "python.h"

we add pybind11 directory as a subdirectory for this project. It will be generate CMakeLists.txt in our pre-defined binary_file (here we use 'pybind_dep')

then we can set target SHARED (means dynamic library) and link it to python static libray. 

Finally, we use pybind11_extension to build this extension file

if everything went well, we can start our make process:

`mkdir build && cd build && cmake .. && devenv bindPY.sln \build Release`

And you can find a "example****.pyd" file in build/Release directory

You can just copy it to your site_packages or other python include directory and rename it to "example.pyd"

### Test

in our example.cc we defined a function *add* which gets two integers and returns the sum of them.

we use
