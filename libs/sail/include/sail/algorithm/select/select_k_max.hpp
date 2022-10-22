#pragma once 
#ifndef SAIL_ALGORITHM_SELECT_KMAX_H_
#define SAIL_ALGORITHM_SELECT_KMAX_H_

#include <sail/algorithm.h>

SAIL_NAMESPACE_BEGIN

// return the kth max indices in an array
double select_k_max(std::vector<double> arr, size_t k, int implement);

SAIL_NAMESPACE_END

#endif // SAIL_ALGORITHM_SELECT_KMAX_H_
