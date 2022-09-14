# Tools.CMAKE

This is the notes to learn cmake

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
