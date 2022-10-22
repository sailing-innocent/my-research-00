#include <sail/algorithm/sort/bubble_sort.hpp>

SAIL_NAMESPACE_BEGIN

void bubble_sort_d(std::vector<double>& arr) {
    for (size_t j = arr.size()-1;j > 1; j--) {
        for (size_t i = 0; i < j; i++) {
            if (arr[i] > arr[j]) {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        } 
    }
}

SAIL_NAMESPACE_END
