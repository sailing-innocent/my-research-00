# Tools.GoogleTest

googletest is a testing framework developed by the Testing Technology team with Google's specific requirements and constraints in mind.

REF: [Googletest Primer | GoogleTest](https://google.github.io/googletest/primer.html)

When using googletest, you start by writing assertions, which are statements that check whether a condition is true.

An assertion's result can be success, nonfatal failure or fatal failure.

## Assertions

ASSERT_* versions generate fatal failures when they fail and abort the current functinos.

EXPECT_* versions generate nonfatal failures, which don't abort the functions.

To provide a custom failure message, simply stream it into the macro

## Simple Tests

To create a test:

- use TEST() macro to define and name a test function
  TEST(TestSuitName, TestName)

## QuickStart CMake

- A compatible operating system
- A compatible C++ compiler that supports at least C++14
- CMake and a compatible build tool for building the project

Here i use the sample to start testing my sail lib

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

enable_testing()

add_executable(ut_sail test/ut_sail.cc)
list(APPEND UT_SAIL_LIBS
    sail
    GTest::gtest_main
)
list(APPEND UT_SAIL_INCLUDES
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(ut_sail PUBLIC ${UT_SAIL_LIBS})
target_include_directories(ut_sail PUBLIC ${UT_SAIL_INCLUDES})

include(GoogleTest)
gtest_discover_tests(ut_sail)
```

And ut_sail.cc

```cpp
#include <sail/sail.h>
#include <gtest/gtest.h>

TEST(HELLOTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}
```
