#include <sail/algorithm/select/select_k_max.hpp>
#include <sail/algorithm/sort/bubble_sort.hpp>

SAIL_NAMESPACE_BEGIN

double select_k_max(std::vector<double> arr, size_t k, int implement) {
    double res;
    
    if (implement == 0) {
        bubble_sort_d(arr);
        if (k < arr.size()) {
            res = arr[k-1];
        }
    }

    return res;
}

SAIL_NAMESPACE_END