# CUDA

## Cuda By Example: An Introduction to General-Purpose GPU Programming

### 2 Get Started
### Chapter C: Introduction to CUDA C

hello.cc
```cpp
#include <iostream>

__global__ void add(int a, int b, int *c) {
    *c = a + b;
}

int main(void) {
    int c;
    int *dev_c;
    cudaMalloc((void**)&dev_c, sizeof(int));
    add<<<1,7>>>(2, 7, dev_c);
    cudaMemcpy(&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost);
    printf("2+7=%d\n", c);
    cudaFree(dev_c);
    return 0;
}
```
CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(HELLO_CUDA CXX CUDA)

if (CUDA_ENABLE)
    message("CUDA is available")
    enable_language(CUDA)
endif()

add_executable(hello hello.cu)
set_target_properties(hello PROPERTIES CUDA_ARCHITECTURES "86")
```

- you can pass pointer allocated with cudaMalloc() to funcitions that execute on the devices
- you can pass pointers allocated with cudaMalloc() to read or write memory from code that executes on the device
- you can pass pointers allocated with cudaMalloc() to functions taht execute on the host
- you cannot use pointers allocated with cudaMalloc() to read or write memory from code that executes on the host

we've seen how to use the host to allocate and free memory on the device, but we've also made it painful clear that you cannot modify this memory from the host.

by using cudaMemcpy, you can access this ointer.

### 3.3 Querying Devices

it would be useful if our program had a way to knowing how much memory and what types of capabilities the device had. Furthermore, it is relatively common for people to have more than one CUDA-capable device per computer. 

Fortunately, there is a very easy interface to determine this information. First, we will want to know how many devices in the system were built on the CUDA architecture -> `cudaGetDeviceCount(&count)`

```cpp
struct cudaDeviceProp {
    char name[256]; // An ASCII string like "NVIDIA GeForce RTX 3060 Laptop GPU"
    size_t totalGlobalMem;  // Global memory in bytes
    size_t sharedMemPerBlock; // the maximum amount of shared memory a single block may use in a bytes.
    int regsPerBlock; // number of 32 bit registers available per block
    int warpSize; // the number of threads in a warp
    size_t memPitch; // the maximum pitch allowed for memory copies in bytes
    int maxThreadsPerBlock; // maximum number of threads that block may contain
    int maxThreadsDim; // The maximum number of threads allowed along each dimentsion of a block
    int MaxGridSize[3];
    size_t totalConstMem;
    int major;
    int minor;
    int clockRate;
    size_t textureAlignment;
    int deviceOverlap;
    int multiProcessorCount;
    int kernelExecTimeoutEnabled;
    int integrated;
    int canMapHostMemory;
    int computeMode;
    int maxTexture1D;
    int maxTexture2D[2];
    int maxTexture3D[3];
    int maxTexture2DArray[3];
    int concurrentKernels;
}

```


### 3.4 Using Device Properties

choose the devices

### 3.5 Chapter Review

## Chapter 4 Parallel Programming in CUDA C

### 4.2 CUDA Parallel Programming

use blockIdx.x to get the block is currently running.

use `add<<<N,1>>>` the first number represents the number of parallel blocks in which we would like the driver to execute our kernel.

For example, if we launch with kernel<<<2,1>>>(), you can think of the runtime creating two copies of kernel.

CUDA C allows you to define a group of blocks in 2 dimensions.

### 4.3 An Example: Julia Set
//TODO remains a project for me

## Chapter 5 Thread Cooperation

by calling `add<<<N,1>>>(dev_a, dev_b, dev_c);` the second parameter actually represents the number of threads per block we want the CUDA runtime to create on our behalf.

$N blocks \times k threads/block = kN parallel threads$

This time, we use thread to implement the previous parallel adding:

as mensioned before, the number of blocks in a single launch is limited, and the number of threads per block cannot exceed `maxThreadPerBlock`

`blockDim` is a built-in variable, a constant for all blocks and stores the number of threads along each dimension of block.

`gridDim` stores a similiar value but for whole grid.

After each threads finishes its work at the current index, we need to increment each of them by the total number of threads running in the grid.

//TODO GPU ripple example

### 5.3 Shared Memory and Synchronization

The CUDA C compiler creates a copy of variable for each block that you launch ont he GPU. Every thread in that block shares the memory.

`__share__ float cache[threadsPerBlock]`
to store each threads' running sum

example dot product:

## Chapter 6 Constant Memory and Events

## Chapter 7 Texture Memory

Texture用于存储只读的纹理，可以是一维或者二维，创建TextureObject，核心类型位cudaTextureObject_t需要包含头文件<texture_types.h>

Surface与Texture不同在于Surface可读可写，核心类型为cudaTextureObject_t

从而可以通过一些方式将OpenGL或者DirectX中注册的Resource空间与Cuda中的Surface空间建立映射，从而不经过CPU进行显存协作。

## Chapter 8 Graphics Interoperability

## Chapter 9 Atomics

## Chapter 10 Streams

## Chapter 11 CUDA C on Multiple GPUs

## Chapter 12 Final Cutdown

## Appendix: Advanced Atomics

