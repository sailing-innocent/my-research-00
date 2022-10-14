cmake_minimum_required(VERSION 3.14)
project(libsail)
OPTION(TEST_ENABLED "build the test suit" ON)
set(TEST_ENABLED TRUE)
# ALGORITHM

list(APPEND LIBSAIL_SRC
    "${PROJECT_SOURCE_DIR}/sail/core/hello.cc"
)

list(APPEND LIBSAIL_INCLUDE
    "${PROJECT_SOURCE_DIR}/include"
)

list(APPEND LIBSAIL_DEP_LIBS
)
list(APPEND LIBSAIL_DEP_DIRS
)

add_library(libsail ${LIBSAIL_SRC})
target_include_directories(libsail PUBLIC ${LIBSAIL_INCLUDE})
target_link_directories(libsail PUBLIC ${LIBSAIL_DEP_DIRS})
target_link_libraries(libsail PUBLIC ${LIBSAIL_DEP_LIBS})

OPTION(BASIC_TEST_ENABLED "basic data structure test enabled" ON)
OPTION(LC_TEST_ENABLED "test the leetcode suit" OFF)

# TESTING
if (TEST_ENABLED)

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

    list(APPEND LIBSAIL_TEST_INCLUDE
        ${LIBSAIL_INCLUDE}
        "E:/includes"
    )

    list(APPEND LIBSAIL_TEST_LIBS
        GTest::gtest_main
        $<TARGET_OBJECTS:libsail>
    )
    
    if (BASIC_TEST_ENABLED)
        list(APPEND BASIC_TEST_SOURCE
            "utest/algorithm/list.test.cc"
            "utest/hello_test.cc"
        )
        add_executable(basic_test ${BASIC_TEST_SOURCE})
        target_include_directories(basic_test PUBLIC ${LIBSAIL_TEST_INCLUDE})
        target_link_libraries(basic_test ${LIBSAIL_TEST_LIBS})
    endif()
    
    if (LC_TEST_ENABLED)
        list(APPEND LC_TEST_SOURCE
            "utest/algorithm/lc01.cc"
        )
        add_executable(lc_test ${LC_TEST_SOURCE})
        target_include_directories(lc_test PUBLIC ${LIBSAIL_TEST_INCLUDE})
        target_link_libraries(lc_test ${LIBSAIL_TEST_LIBS})
    endif()
    
    include(GoogleTest)
    gtest_discover_tests(lc_test)
endif()

