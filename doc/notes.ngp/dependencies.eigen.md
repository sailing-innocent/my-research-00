# eigen library

https://eigen.tuxfamily.org/

eigen is a header-only template library. So we don't need to compile before using it. The CMakeLists.txt system in source code is just used for documentation and test cases.

尝试编译了一下，电脑直接崩了。果然还是配置太低了wwww。

使用eigen的方法比想象中容易得多。

新建一个空文件夹，照例写歌test.cc

```cpp
#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;

int main() 
{
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;
    return 0;
}
```

并新建一个CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.18)
project(eigenTest)
include_directories("../../dependencies/eigen")
add_executable(test01 test.cc)

```

然后惯例编译运行，就可以了
