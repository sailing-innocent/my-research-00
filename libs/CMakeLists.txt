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