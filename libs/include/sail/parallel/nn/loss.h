/**
 * @file loss.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once 

#include <sail/common.h>
// gpu-matrix
// object

SAIL_NAMESPACE_BEGIN

template <typename T>
class Loss: public ObjectWithMutableHyperparams {
public:
    virtual void evaluate(
        // cudaStream_t stream;
        const uint32_t stride,
        const uint32_t dims,
        const float loss_scale,
        // GPUMatrix<T> predict
        // GPUMatrix target
        // GPUMatrix values
        // GPUMatrix gradients
        // GPUMatrix data_pdf
    ) const = 0;
}

SAIL_NAMESPACE_END
