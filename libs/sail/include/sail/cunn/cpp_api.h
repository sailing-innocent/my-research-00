/**
 * @file: include/sail/cunn/cpp_api.h
 * @author: sailing-innocent
 * @create: 2022-10-26
 * @desp: The CPP API for cuda nn library
*/

#pragma once
#ifndef SAIL_CUNN_CPP_API_H_
#define SAIL_CUNN_CPP_API_H_

#include <json/json.hpp>

#include <cuda_runtime.h>

#include <memory>
#include <string>

#include <sail/cunn/common.h>

SAIL_CUNN_NAMESPACE_BEGIN

struct Context {
    Context() = default;
    virtual ~Context() {}
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;
};

namespace cpp {

using json = nlohmann::json;

enum EPrecision {
	Fp32,
	Fp16,
};

EPrecision preferred_precision();

uint32_t batch_size_granularity();

void free_temporary_memory();

int cuda_device();
void set_cuda_device(int device);

struct Context {
	std::unique_ptr<tcnn::Context> ctx;
};

class Module {
public:
	Module(EPrecision param_precision, EPrecision output_precision) 
	: m_param_precision{param_precision}, 
	  m_output_precision{output_precision} {}
	virtual ~Module() {}

	virtual void inference(cudaStream_t stream, uint32_t n_elements, const float* input, void* output, void* params) = 0;
	virtual Context forward(cudaStream_t stream, uint32_t n_elements, const float* input, void* output, void* params, bool prepare_input_gradients) = 0;
	virtual void backward(cudaStream_t stream, const Context& ctx, uint32_t n_elements, float* dL_dinput, const void* dL_doutput, void* dL_dparams, const float* input, const void* output, const void* params) = 0;
	virtual void backward_backward_input(cudaStream_t stream, const Context& ctx, uint32_t n_elements, const float* dL_ddLdinput, const float* input, const void* dL_doutput, void* dL_dparams, void* dL_ddLdoutput, float* dL_dinput, const void* params) = 0;

	virtual uint32_t n_input_dims() const = 0;

	virtual size_t n_params() const = 0;
	EPrecision param_precision() const {
		return m_param_precision;
	}

	virtual void initialize_params(size_t seed, float* params_full_precision) = 0;

	virtual uint32_t n_output_dims() const = 0;
	EPrecision output_precision() const {
		return m_output_precision;
	}

	virtual json hyperparams() const = 0;
	virtual std::string name() const = 0;

private:
	EPrecision m_param_precision;
	EPrecision m_output_precision;
};

Module* create_network_with_input_encoding(uint32_t n_input_dims, uint32_t n_output_dims, const json& encoding, const json& network);
Module* create_network(uint32_t n_input_dims, uint32_t n_output_dims, const json& network);
Module* create_encoding(uint32_t n_input_dims, const json& encoding, EPrecision requested_precision);

}

SAIL_CUNN_NAMESPACE_END

#endif // SAIL_CUNN_CPP_API_H_
