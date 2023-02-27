cmake_minimum_required(VERSION 3.0.0)
project(test)
set(SOURCES ./src/main.c)
add_executable(test ${SOURCES})

target_link_libraries(test glfw GLEW OpenGL m SOIL)
