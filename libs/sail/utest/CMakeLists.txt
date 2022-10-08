cmake_minimum_required(VERSION 3.14)

OPTION(BASIC_TEST_ENABLED "basic data structure test enabled" ON)
OPTION(LC_TEST_ENABLED "test the leetcode suit" OFF)

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
    "${PROJECT_SOURCE_DIR}/../include"
)

list(APPEND LIBSAIL_TEST_LIBS
    GTest::gtest_main
)

if (BASIC_TEST_ENABLED)
    list(APPEND BASIC_TEST_SOURCE
        "algorithm/list.test.cc"
    )
    add_executable(basic_test ${BASIC_TEST_SOURCE})
    target_include_directories(basic_test PUBLIC ${LIBSAIL_INCLUDE_DIR})
    target_link_libraries(basic_test ${LIBSAIL_TEST_LIBS})
endif()

if (LC_TEST_ENABLED)
    list(APPEND LC_TEST_SOURCE
        "algorithm/lc01.cc"
    )
    add_executable(lc_test ${LC_TEST_SOURCE})
    target_include_directories(lc_test PUBLIC ${LIBSAIL_INCLUDE_DIR})
    target_link_libraries(lc_test ${LIBSAIL_TEST_LIBS})
endif()

include(GoogleTest)
gtest_discover_tests(lc_test)