cmake_minimum_require(VERSION 3.18)

project(research-00
    VERSION 0.1
    DESCRIPTION "my-research-00"
    LANGUAGE C CXX CUDA
)

set(RES_VERSION "${CMAKE_PROJECT_VERSION}")

if (NOT RES_DEPLOY)
    set(RES_VERSION "${RES_VERSION}dev")
endif()

option(RES_BUILD_WITH_GUI "Build with GUI support (requires GLFW and GLEW)?" ON)
option(RES_BUILD_WITH_VULKAN "Build with Vulkan to enable DLSS support?" ON)
option(RES_BUILD_WITH_OPTIX "Build with OptiX to enable hardware ray tracing?" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set default configuration
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No release type specified. Setting to 'Release'.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif()

if (NOT EXISTING "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/CMakeLists.txt")
    message(FATAL_ERROR
        "some research00 dependencies are missing. "
    )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP24")


###############################################################################
# CUDA compiler setup
###############################################################################
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS OFF)
set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)
set(CMAKE_CUDA_RUNTIME_LIBRARY Shared)

list(APPEND CUDA_NVCC_FLAGS "-Xcompiler=-bigobj")

list(APPEND CUDA_NVCC_FLAGS "--entended-lambda")
list(APPEND CUDA_NVCC_FLAGS "--expt-relaxed-constexpr")

###############################################################################
# Dependencies
###############################################################################

set(TCNN_BUILD_BENCHMARK OFF)
set(TCNN_BUILD_EXAMPLES OFF)
add_subdirectory(dependencies/tiny-cuda-nn)

set(CMAKE_CUDA_ARCHITECTURES ${TCNN_CUDA_ARCHITECTURES})

if (RES_BUILD_WITH_GUI)
    find_package(Vulkan)
    if (Vulkan_FOUND AND RES_BUILD_WITH_VULKAN)
    else()
        set(RES_VULKAN OFF)
        if (RES_BUILD_WITH_VULKAN)
            message(WARNING
                "Vulkan was not found."
            )
        endif()
    endif()

    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_INSTALL OFF CACHE BOOL " " FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL " " FORCE)
    set(GLFW_USE_CHDIR OFF CACHE BOOL " " FORCE)
    set(GLFW_VULKAN_STATIC OFF CACHE BOOL " " FORCE)
    set(BUILD_SHARED_LIBS ON CACHE BOOL " " FORCE)

    add_subdirectory(dependencies/glfw)
    set_target_properties(glfw PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

    mark_as_advanced(
		GLFW_BUILD_DOCS GLFW_BUILD_EXAMPLES GLFW_BUILD_INSTALL GLFW_BUILD_TESTS
		GLFW_DOCUMENT_INTERNALS GLFW_INSTALL GLFW_USE_CHDIR GLFW_USE_MENUBAR
		GLFW_USE_OSMESA GLFW_VULKAN_STATIC GLFW_USE_RETINA GLFW_USE_MIR
		BUILD_SHARED_LIBS USE_MSVC_RUNTIME_LIBRARY_DLL
    )

    list(APPEND RES_INCLUDE_DIRECTORIES "dependencies/glfw/include" "dependencies/imgui")

    list(APPEND RES_INCLUDE_DIRECTORIES "dependencies/gl3w")
    list(APPEND GUI_SOURCES "dependencies/gl3w/GL/gl3w.c")
    set(RES_LIBRARIES ${RES_LIBRARIES} GL ${GLEW_LIBRARIES} $<TARGET_OBJECTS:glfw_objects> ${CMAKE_DL_LIBS})

    list(APPEND GUI_SOURCES
        dependencies/imguizmo/ImGuizmo.cpp
		dependencies/imgui/imgui.cpp
		dependencies/imgui/backends/imgui_impl_glfw.cpp
		dependencies/imgui/backends/imgui_impl_opengl3.cpp
		dependencies/imgui/imgui_draw.cpp
		dependencies/imgui/imgui_tables.cpp
		dependencies/imgui/imgui_widgets.cpp
    )
    list(APPEND RES_DEFINITIONS -DRES_GUI)
endif(RES_BUILD_WITH_GUI)

#[[
list(APPEND RES_INCLUDE_DIRECTORIES
    "dependencies"
    "dependencies/eigen"
    "dependencies/filesystem"
    "dependencies/nanovdb"
    "dependencies/tinylogger"
)
]]

###############################################################################
# Program
###############################################################################

list(APPEND RES_DEFINITIONS -DRES_VERSION="${RES_VERSION}")
list(APPEND RES_INCLUDE_DIRECTORIES "include")
list(APPEND RES_SOURCES
    ${GUI_SOURCES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})

get_filename_component(CUDA_COMPILER_BIN "${CMAKE_CUDA_COMPILER}" DIRECTORY)

if (RES_OPTIX)
endif()

add_library(res STATIC ${RES_SOURCES})
set_target_properties(res PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON CUDA_SEPARABLE_COMPILATION ON)
target_compile_definitions(res PUBLIC ${RES_DEFINITIONS})
target_compile_options(res PUBLIC $<$<COMPILE_LANGUAGE:CUDA>:${CUDA_NVCC_FLAGS}>)
target_include_directories(res PUBLIC ${RES_INCLUDE_DIRECTORIES})
target_link_directories(res PUBLIC ${RES_LINK_DIRECTORIES})
# target_link_libraries(res PUBLIC ${RES_LIBRARIES} tiny-cuda-nn)

add_executable(testbed src/main.cu)
target_link_libraries(testbed PRIVATE res)
