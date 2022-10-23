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
    if (implement == 1) {
        std::vector<double> window;
        for (size_t i = 0; i < k; i++) {
            window[i] = arr[i];
        }
        bubble_sort_d(window);
        for (size_t i = k; i < arr.size(); i++) {
            size_t j = k-1;
            if (window[j] <= arr[i]) {
                window[j] = arr[i];
                continue;
            }
            while (window[j] > arr[i] && j >= 0) {
                j--;
            }
            window[j] = arr[i];
        }
        res = window[k-1];
    }

    return res;
}

SAIL_NAMESPACE_END