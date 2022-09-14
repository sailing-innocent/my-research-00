# Tools.Compiler

## Linux.G++

- -Wall: all warnings
- -shared: 尽量使用动态库
- -fPIC: 适用于动态链接库无关目标码

## Window.CL

this is the note for cl.exe, which is the compiler for C++ in Windows

https://docs.microsoft.com/en-us/cpp/build/referenc

## Hello World

main.cpp:

```cpp
#include <iostream>
using namespace std;
int main() {
	cout << "Hello World!" << endl;
	return 0;
}
```

And compile it with

`cl /EHsc main.cpp`

to get main.exe to print "Hello World" on your console.

support for C++14: `/std:c++14`
