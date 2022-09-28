cmake_minimum_required(VERSION 3.10)

project(learn C CXX)

set(GLFW_INCLUDE_DIR "E:/libs/glfw/include")
set(GLFW_LIB_DIR "E:/libs/")
set(GLAD_INCLUDE_DIR "E:/libs/glad/include")
set(GLAD_SOURCE "E:/libs/glad/src/glad.c")

list(APPEND LEARN_SOURCE
    ${GLAD_SOURCE}
    main.cc
)

list(APPEND LEARN_INCLUDE_DIR 
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
)

list(APPEND LEARN_LIB_DIR
    ${GLFW_LIB_DIR}
)

list(APPEND LEARN_LIBRARIES
    glfw3
)

list(APPEND LEARN_COMPILE_DEF
    ${GLAD_COMPILE_DEFINITION}
)

add_executable(main ${LEARN_SOURCE})
target_include_directories(main PUBLIC ${LEARN_INCLUDE_DIR})
target_link_directories(main PUBLIC ${LEARN_LIB_DIR})
target_link_libraries(main PUBLIC ${LEARN_LIBRARIES})
set_property(TARGET main APPEND PROPERTY LINK_FLAGS "/NODEFAULTLIB:MSVCRT")

