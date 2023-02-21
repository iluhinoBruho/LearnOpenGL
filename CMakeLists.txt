cmake_minimum_required(VERSION 3.0.0)
project(test)
set(SOURCES ./src/main.c)
add_executable(test ${SOURCES})

target_link_libraries(test glfw GLEW OpenGL m)

# cmake_minimum_required(VERSION 3.0.0)
# project(learn_opengl_project VERSION 0.1.0)

# add_executable(learn_opengl_project src/main.c)

# if(POLICY CMP0072)
#     cmake_policy(SET CMP0072 NEW)
# endif()

# find_package(GLEW REQUIRED)
# find_package(OpenGL REQUIRED)
# include_directories(${GLEW_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS})
# link_libraries(${GLEW_LIBRARIES} ${OpenGL_LIBRARIES})
# add_dependencies(learn_opengl_project OpenGL::OpenGL)

# target_link_libraries(learn_opengl_project glfw GLEW::GLEW OpenGL::OpenGL) #${OpenGL_LIBRARIES})

# include(CTest)
# enable_testing()

#SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -o test.elf -Wall -lGL -lGLU -lglut -lGLEW -lglfw")
#SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -o test.elf -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor")


#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
