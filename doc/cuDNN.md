# NVIDIA cuDNN

- This cuDNN 8.6.0 Developer Guide provides an overview of the NVIDIA cuDNN features such as customizable layouts, supporting flexible dimension ordering, and subregions for the 4D tensors used as inputs and outputs to all of its routines. This flexibility allows easy integration into any neural network implementation.

## Introduction

NVIDIA CUDA Deep Neural Library (cuDNN) is a GPU-accelerated library of primitives for deep neural networks. It provides highly tuned implementations of routines in DNN applications:
    - Comvolution forward and backward, including cross-correlation
    - Matrix multiplication
    - Pooling forward and backward
    - Softmax forward and backward
    - Neuron activations forward and backward: relu, tanh, sigmoid, elu, gelu, softplus, switch
    - Arithmetic, mathematical, relational and logical pointwise operations
    - Tensor transformation functions
    - LRN, LCN and batch normalization forward and background

An application using cuDNN must initialize a handle to the library context by calling `cudnnCreate()` and associated with `cudnnDestroy()`

an application