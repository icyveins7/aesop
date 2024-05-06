cmake_minimum_required(VERSION 3.20)

project(aesop)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

# Check if on MacOS
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "" FORCE)
    message("CMAKE_OSX_ARCHITECTURES is " ${CMAKE_OSX_ARCHITECTURES})
endif()

# Add GLM submodule things?
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/glm
)

# Add opengl things
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
message("Including GLEW from " ${GLEW_INCLUDE_DIRS})
# link_libraries(${GLEW_LIBRARIES})
# message("Linking GLEW from " ${GLEW_LIBRARIES})

find_package(glfw3 REQUIRED)

# Add our includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add our one example for now
add_executable(
    example
    src/main.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/Shader.cpp
    src/Window.cpp
)
target_link_libraries(
    example PUBLIC GLEW::GLEW
)




