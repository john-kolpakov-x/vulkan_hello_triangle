cmake_minimum_required(VERSION 3.23)
project(vulkan_hello_triangle)

find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glfw3 REQUIRED FATAL_ERROR)
find_package(glm REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++17 -O2")

add_executable(vulkan_hello_triangle main.cpp HelloTriangleApp.cpp HelloTriangleApp.h)
target_link_libraries (vulkan_hello_triangle glfw)
target_link_libraries (vulkan_hello_triangle ${Vulkan_LIBRARY})
target_link_libraries (vulkan_hello_triangle ${CMAKE_DL_LIBS})

target_compile_options(vulkan_hello_triangle PUBLIC "-pthread")
target_compile_options(vulkan_hello_triangle PUBLIC "-lX11")
target_compile_options(vulkan_hello_triangle PUBLIC "-lXxf86vm")
target_compile_options(vulkan_hello_triangle PUBLIC "-lXrandr")
target_compile_options(vulkan_hello_triangle PUBLIC "-lXi")
