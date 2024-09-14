cmake_minimum_required(VERSION 3.5)

project(TestProject)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(TestProject src/main.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp src/Shader.cpp src/default.vert src/default.frag)

target_link_libraries(TestProject glfw OpenGL::GL)