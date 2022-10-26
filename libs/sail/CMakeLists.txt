cmake_minimum_required(VERSION 3.14)
project(libsail)

set(TEST_ENABLED TRUE)
set(BASIC_TEST_ENABLED FALSE)
set(DEPS_TEST_ENABLED FALSE)
set(ALGORITHM_TEST_ENABLED TRUE)
set(LC_TEST_ENABLED FALSE)
# ALGORITHM
aux_source_directory("sail/algorithm" ALGORITHM_SRC)

list(APPEND LIBSAIL_SRC
    "sail/hello.cc"
    # ${ALGORITHM_SRC}
    # "sail/core/timer.cc"
)

list(APPEND LIBSAIL_INCLUDE
    "include"
)

list(APPEND LIBSAIL_DEP_LIBS
    #fmtd
)
list(APPEND LIBSAIL_DEP_DIRS
    "E:/libs/fmt"
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
        # EIGEN
        "E:/libs/eigen/"
    )

    list(APPEND LIBSAIL_TEST_LIBS
        ${LIBSAIL_DEP_LIBS}
        GTest::gtest_main
        $<TARGET_OBJECTS:libsail>
    )

    list(APPEND LIBSAIL_TEST_LIBDIRS
        ${LIBSAIL_DEP_DIRS}
    )

    include(GoogleTest)

    if (${BASIC_TEST_ENABLED})
        list(APPEND BASIC_TEST_SOURCE
            # "utest/hello_test.cc"
            # "utest/core/timer.test.cc"
            # "utest/core/cpp_basic.test.cc"
            "utest/core/cpp_macro.test.cc"
            # "utest/core/stl_vector.test.cc"
        )
        add_executable(basic_test ${BASIC_TEST_SOURCE})
        target_include_directories(basic_test PUBLIC ${LIBSAIL_TEST_INCLUDE})
        target_link_libraries(basic_test ${LIBSAIL_TEST_LIBS})
        gtest_discover_tests(basic_test)
    endif()

    if (${ALGORITHM_TEST_ENABLED})
        list(APPEND ALGORITHM_TEST_SOURCE
            "utest/algorithm/node.test.cc"
            "utest/algorithm/list.test.cc"
            "utest/algorithm/dlist.test.cc"
            # "utest/algorithm/sort.test.cc"
            # "utest/algorithm/select.test.cc"
        )
        add_executable(algo_test ${ALGORITHM_TEST_SOURCE})
        target_include_directories(algo_test PUBLIC ${LIBSAIL_TEST_INCLUDE})
        target_link_libraries(algo_test ${LIBSAIL_TEST_LIBS})
        gtest_discover_tests(algo_test)
    endif()

    if (${DEPS_TEST_ENABLED})
        list(APPEND DEPS_TEST_SOURCE
            # "utest/dependencies/eigen_basic.test.cc" 
            "utest/dependencies/fmt.test.cc"
        )
        add_executable(deps_test ${DEPS_TEST_SOURCE})
        target_include_directories(deps_test PUBLIC ${LIBSAIL_TEST_INCLUDE})
        target_link_libraries(deps_test ${LIBSAIL_TEST_LIBS})
        target_link_directories(deps_test PUBLIC ${LIBSAIL_TEST_LIBDIRS})
        gtest_discover_tests(deps_test)
    endif()
    
    if (${LC_TEST_ENABLED})
        list(APPEND LC_TEST_SOURCE
            "utest/leetcode/lc01.cc"
        )
        add_executable(lc_test ${LC_TEST_SOURCE})
        target_include_directories(lc_test PUBLIC ${LIBSAIL_TEST_INCLUDE})
        target_link_libraries(lc_test PRIVATE ${LIBSAIL_TEST_LIBS})
        gtest_discover_tests(lc_test)
    endif()
    

endif()

