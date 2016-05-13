cmake_minimum_required(VERSION 3.5)
project(LearnOpenGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

set(GL_LIBS ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})

# Executables
add_executable(hellowindow src/hellowindow.cpp)
target_link_libraries(hellowindow ${GL_LIBS})

add_executable(hellotriangle src/hellotriangle.cpp)
target_link_libraries(hellotriangle ${GL_LIBS})

add_executable(hellotriangle_ebo src/hellotriangle_ebo.cpp)
target_link_libraries(hellotriangle_ebo ${GL_LIBS})

add_executable(shaders src/shaders.cpp)
target_link_libraries(shaders ${GL_LIBS})

add_executable(textures src/textures.cpp)
target_link_libraries(textures ${GL_LIBS})
