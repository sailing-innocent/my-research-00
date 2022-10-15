# LIBSAIL_CORE
- log
- debug
- file
- database
- thread
- io
- platform
- STL encrypt
- utility functions (swap, lerp...)


## Chrono

Durations: measure time spans, like: one minute, two hours or ten miliseconds

Timepoint: A reference to a specific point in time. 

clocks


```cpp
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

int main() {
    using namespace std::chrono;

    steady_clock::time_point t1 = steady_clock::now();
    
    // Process

    steady_clock::time_point t2 = steady_clock::now();
}
```