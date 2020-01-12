cmake_minimum_required(VERSION 3.3)
project(hw3-test)

# The main executable
add_executable(main
        Main.cpp
        OpenGL.h
        Opengl.cpp
        Shader.hpp
        Shader.cpp
        Sphere.h Sphere.cpp)

set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)
