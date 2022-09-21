cmake_minimum_required(VERSION 3.18)

project(my-ngp
    VERSION 0.1
)
add_definitions("-DUNICODE" "-D_UNICODE")

message(STATUS "CUDA LIBRARIES: ${CUDA_LIBRARIES}")

set(NGP_VERSION "${CMAKE_PROJECT_VERSION}")
set(RESEARCH_ROOT_DIR "${PROJECT_SOURCE_DIR}/../../")

option(NGP_BUILD_WITH_GUI "Build WIth GUI support with GLFW and GLEW" ON)
option(NGP_BUILD_WITH_VULKAN "Build with Vulkan to enable DLSS support" ON)
option(NGP_BUILD_WITH_OPTIX "Build With OptixX to enable hardware ray tracing" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Build type and C++ compiler setup

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No release type specified. Setting to 'Release'")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Coose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif()

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/glfw/CMakeLists.txt")
    message(FATAL_ERROR
        "glfw not available"
    )
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP24")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

# CUDA SETUP

set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS OFF)
set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)
set(CMAKE_CUDA_RUNTIME_LIBRARY Shared)

if(MSVC)
    list(APPEND CUDA_NVCC_FLAGS "-Xcompiler=-bigobj")
else()
endif()

list(APPEND CUDA_NVCC_FLAGS "--extended-lambda")
list(APPEND CUDA_NVCC_FLAGS "--expt-relaxed-constexpr")

# Dependencies

set(TCNN_BUILD_BENCHMARK OFF)
set(TCNN_BUILD_EXAMPLES OFF)
add_subdirectory("${RESEARCH_ROOT_DIR}/dependencies/tiny-cuda-nn" "tiny-cuda-nn")

# list(APPEND NGP_LINK_DIRECTORIES "${RESEARCH_ROOT_DIR}/dependencies/tiny-cuda-nn/build")

# set(CMAKE_CUDA_ARCHITECTURES ${TCNN_CUDA_ARCHITECTURES})
# message("NOW CUDA: ${TCNN_CUDA_ARCHITECTURES}")

# set(NGP_BUILD_WITH_GUI OFF)
if (NGP_BUILD_WITH_GUI)
    find_package(Vulkan)
    if (Vulkan_FOUND AND NGP_BUILD_WITH_VULKAN)
        message("Build with Vulkan")
        set(NGP_VULKAN ON)
        list(APPEND NGP_DEFINITIONS -DNGP_VULKAN -DGLFW_INCLUDE_VULKAN)
        list(APPEND NGP_INCLUDE_DIRECTORIES "${Vulkan_INCLUDE_DIRS}")
        set(NGP_LIBRARIES ${NGP_LIBRARIES} ${Vulkan_LIBRARIES})

        # list(APPEND GUI_SOURCES src/dlss.cu)
        list(APPEND NGP_INCLUDE_DIRECTORIES "${RESEARCH_ROOT_DIR}/dependencies/dlss/include")
        if (MSVC)
            list(APPEND NGP_LINK_DIRECTORIES "${RESEARCH_ROOT_DIR}/dependencies/dlss/lib/Windows_x86_64/x86_64")
            if (CMAKE_BUILD_TYPE STREQUAL "Debug")
                set(NGP_LIBRARIES ${NGP_LIBRARIES} nvsdk_ngx_d_dbg)
            else()
                set(NGP_LIBRARIES ${NGP_LIBRARIES} nvsdk_ngx_d)
            endif()
        endif()
    else()
        message("NOT BUILDING WITH VULKAN")
    endif()

	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL " " FORCE)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL " " FORCE)
	set(GLFW_BUILD_INSTALL OFF CACHE BOOL " " FORCE)
	set(GLFW_INSTALL OFF CACHE BOOL " " FORCE)
	set(GLFW_USE_CHDIR OFF CACHE BOOL " " FORCE)
	set(GLFW_VULKAN_STATIC OFF CACHE BOOL " " FORCE)
	set(BUILD_SHARED_LIBS ON CACHE BOOL " " FORCE)

    add_subdirectory("${RESEARCH_ROOT_DIR}/dependencies/glfw" "glfw")

    set_target_properties(glfw PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFUALT_BUILD 1)
	mark_as_advanced(
		GLFW_BUILD_DOCS GLFW_BUILD_EXAMPLES GLFW_BUILD_INSTALL GLFW_BUILD_TESTS
		GLFW_DOCUMENT_INTERNALS GLFW_INSTALL GLFW_USE_CHDIR GLFW_USE_MENUBAR
		GLFW_USE_OSMESA GLFW_VULKAN_STATIC GLFW_USE_RETINA GLFW_USE_MIR
		BUILD_SHARED_LIBS USE_MSVC_RUNTIME_LIBRARY_DLL
	)


    list(APPEND NGP_INCLUDE_DIRECTORIES "${RESEARCH_ROOT_DIR}/dependencies/glfw/include" "${RESEARCH_ROOT_DIR}/dependencies/imgui")

    if (MSVC)
        list(APPEND NGP_INCLUDE_DIRECTORIES "${RESEARCH_ROOT_DIR}/dependencies/gl3w")
        list(APPEND GUI_SOURCES "${RESEARCH_ROOT_DIR}/dependencies/gl3w/GL/gl3w.c")
        set(NGP_LIBRARIES ${NGP_LIBRARIES} opengl32 $<TARGET_OBJECTS:glfw_objects>)
    endif()

    list(APPEND GUI_SOURCES
        "${RESEARCH_ROOT_DIR}/dependencies/imguizmo/ImGuizmo.cpp"
        "${RESEARCH_ROOT_DIR}/dependencies/imgui/imgui.cpp"
        "${RESEARCH_ROOT_DIR}/dependencies/imgui/backends/imgui_impl_glfw.cpp"
        "${RESEARCH_ROOT_DIR}/dependencies/imgui/backends/imgui_impl_opengl3.cpp"
        "${RESEARCH_ROOT_DIR}dependencies/imgui/imgui_draw.cpp"
        "${RESEARCH_ROOT_DIR}/dependencies/imgui/imgui_tables.cpp"
        "${RESEARCH_ROOT_DIR}/dependencies/imgui/imgui_widgets.cpp"
    )

    list(APPEND NGP_DEFINITIONS -DNGP_GUI)
endif(NGP_BUILD_WITH_GUI)

list(APPEND NGP_INCLUDE_DIRECTORIES
    "${RESEARCH_ROOT_DIR}/dependencies"
    "${RESEARCH_ROOT_DIR}/dependencies/eigen"
    # "${RESEARCH_ROOT_DIR}/dependencies/filesystem"
    # "dependencies/nanovdb"
    # "dependencies/tinylogger"
)

# find_package(OpenMP)
# find_package(OptiX)
# find_package(Python 3.7 COMPONENTS Interpreter Development)

# Program

list(APPEND NGP_DEFINITIONS -DNGP_VERSION="${NGP_VERSION}" "-DTCNN_CUDA_ARCHITECTURES=86")
list(APPEND NGP_INCLUDE_DIRECTORIES "${RESEARCH_ROOT_DIR}/include")
list(APPEND NGP_SOURCES
    ${GUI_SOURCES}
    src/testbed.cu
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})

get_filename_component(CUDA_COMPILER_BIN "${CMAKE_CUDA_COMPILER}" DIRECTORY)

add_library(ngp STATIC ${NGP_SOURCES})
set_target_properties(ngp PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON CUDA_SEPARABLE_COMPILATION ON)
target_compile_definitions(ngp PUBLIC ${NGP_DEFINITIONS})
target_compile_options(ngp PUBLIC $<$<COMPILE_LANGUAGE:CUDA>:${CUDA_NVCC_FLAGS}>)
target_include_directories(ngp PUBLIC ${NGP_INCLUDE_DIRECTORIES})
target_link_directories(ngp PUBLIC ${NGP_LINK_DIRECTORIES})
target_link_libraries(ngp PUBLIC ${NGP_LIBRARIES} tiny-cuda-nn cuda cudart)


add_executable(testbed src/main0.cu)
target_link_libraries(testbed PRIVATE ngp PUBLIC cuda cudart)
