cmake_minimum_required(VERSION 3.14)
project(libsail_test)

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

add_executable(lc_test algorithm/lc01.cc)
target_include_directories(lc_test PUBLIC ${LIBSAIL_INCLUDE_DIR})
target_link_libraries(lc_test ${LIBSAIL_TEST_LIBS})

include(GoogleTest)
gtest_discover_tests(lc_test)