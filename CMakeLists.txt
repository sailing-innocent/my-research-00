cmake_minimum_required(VERSION 3.10)

project(my-research-00
    VERSION 0.1
    LANGUAGES C CXX CUDA
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
else()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set (PLANE_DRAW TRUE)

set(LIBSAIL_DIR "libs/sail/build/Debug")
set(LIBING_DIR "libs/ing/build/Debug")
set(LIBSAIL_INCLUDE "libs/sail/include")
set(LIBING_INCLUDE "libs/ing/include")


if (${PLANE_DRAW})
    list(APPEND DRAW_LIBS_DIR
        ${LIBSAIL_DIR}
        ${LIBING_DIR}
        "E:/libs/glfw"
        "E:/sdk/Vulkan/Lib"
    )

    list(APPEND DRAW_INCLUDE
        ${LIBSAIL_INCLUDE}
        ${LIBING_INCLUDE}
        "E:/libs/eigen/"
        "E:/sdk/Vulkan/Include"
        "E:/includes"
    )

    list(APPEND DRAW_LIBS
        "glfw3"
        "vulkan-1"
        "libsail" 
        "ing"
    )

    list(APPEND DRAW_SOURCE
        "src/plane_draw.cc"
    )
    add_executable(draw ${DRAW_SOURCE})
    target_link_directories(draw PUBLIC ${DRAW_LIBS_DIR})
    target_link_libraries(draw PUBLIC ${DRAW_LIBS})
    target_include_directories(draw PUBLIC ${DRAW_INCLUDE})
endif()