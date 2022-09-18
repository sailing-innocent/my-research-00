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

# option(USE_SAIL "Use Sail library implementation" ON)
