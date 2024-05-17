cmake_minimum_required(VERSION 3.20)

project(aesop)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

# Check if on MacOS
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "" FORCE)
    message("CMAKE_OSX_ARCHITECTURES is " ${CMAKE_OSX_ARCHITECTURES})
    message("If you are on Apple Silicon, be sure to install x86 GLEW and glfw libraries through brew.")
endif()

# Add GLM submodule things?
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/glm
)

# Add opengl things
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
message("Including OpenGL from " ${OPENGL_INCLUDE_DIRS})

# Add glew things
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
message("Including GLEW from " ${GLEW_INCLUDE_DIRS})

# Add glfw, this doesn't actually define things
# Just place 'glfw' in the target
find_package(glfw3 REQUIRED)

# Add our includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add our one example for now
add_executable(
    line_example
    src/main.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/Shader.cpp
    src/Window.cpp
)
target_link_libraries(
    line_example PUBLIC GLEW::GLEW OpenGL::GL glfw
)

# Add an example for heatmap squares





