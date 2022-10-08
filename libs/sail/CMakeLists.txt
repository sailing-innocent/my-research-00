cmake_minimum_required(VERSION 3.14)
project(libsail)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

list(APPEND LIBSAIL_INCLUDE_DIR
    "E:/includes"
    "${PROJECT_SOURCE_DIR}/include"
)

list(APPEND LIBSAIL_TEST_LIBS
    GTest::gtest_main
)

add_executable(hello_test utest/hello_test.cc)
target_include_directories(hello_test PUBLIC ${LIBSAIL_INCLUDE_DIR})
target_link_libraries(hello_test ${LIBSAIL_TEST_LIBS})

include(GoogleTest)
gtest_discover_tests(hello_test)