cmake_minimum_required(VERSION 3.14)
project(libsail)
OPTION(TEST_ENABLED "build the test suit" ON)

# ALGORITHM

# TESTING
if (TEST_ENABLED)
    add_subdirectory(utest)
endif()
