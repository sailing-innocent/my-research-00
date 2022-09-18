# Tools.CMAKE

This is the notes to learn cmake

[CMake Tutorial — CMake 3.24.2 Documentation](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

## Hello World

in an empty directory, create a file called CMakeLists.txt and main.cc

```cmake
cmake_minimum_requirement(VERSION 3.4)
project(DEMO_1)
add_executable(Demo main.cc)
```

and main.cc

```cc
#include <iostream>

int main() {
    std::cout << "Hello CMake!" << std::endl;
    return 0;
}
```

Then we can

`mkdir build & cd build & cmake .. `

to generate the .sln file

then use devenv to compile

`devenv DEMO_1.sln /build Debug `

set CXX standard: 

`set(CMAKE_CXX_STANDARD 11)`

`set(CMAKE_CXX_STANDARD_REQUIRED True)`

## Build Libraries

use cmake to make your own util library and its corresponding test framework.

start by create an empty directory `mkdir libs`

And create an CMakeLists under libs

Suppose we are going to build our library named "sail" and place our test code into directory test, you can build a dir tree like this:

- libs
  - inlcude
    - sail/sail.h
  - sail
    - algo
    - optim
    - ...
    - sail.cc
    - CMakeLists.txt
  - test
    - ut_sail.cc
  - CMakeLists.txt

The CMakeLists.txt in ./sail directory will build the library:

```cmake
cmake_minimum_required(VERSION 3.18)
project(libsail)
add_library(sail sail.cc)
```

And the Definition of this library can found in ./include/sail/sail.h

```cpp
namespace sail {
    int add(int a, int b);
}
```

We are going to place our test code in ./test/ut_sail.cc to execute the unit test for sail library:

```cpp
#include <iostream>
#include <sail/sail.h>

int main() {
    std::cout << "This is the Unit Test for SAIL Library" << std::endl;
    std::cout << "The result of 1 + 2 is : " << sail::add(1,2) << std::endl;
    return 0;
}

```

Now we can include googletest framework in CMakeLists.txt of the root

```cmake
cmake_minimum_required(VERSION 3.18)
project(test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(sail)
add_executable(ut_sail test/ut_sail.cc)
target_link_libraries(ut_sail PUBLIC sail)
list(APPEND UT_SAIL_INCLUDES
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)
target_include_directories(ut_sail PUBLIC ${UT_SAIL_INCLUDES})
```

The formal way to build it, You can get the exciting result!
