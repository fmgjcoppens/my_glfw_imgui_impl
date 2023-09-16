cmake_minimum_required(VERSION 3.16)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(GLFW_BUILD_DOCS OFF)    
set(GLFW_BUILD_TESTS OFF)    
set(GLFW_BUILD_EXAMPLES OFF)    
add_subdirectory(glfw)

add_subdirectory(imgui)

file(GLOB SOURCES src/*.cpp)
set(SOURCES ${SOURCES} imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_glfw.cpp)
#set(SOURCES ${SOURCES})

file(GLOB HEADERS include/*.hpp)

message(STATUS "SOURCES = ${SOURCES}")

add_executable(MyApp ${SOURCES} ${HEADERS})
target_include_directories(MyApp PRIVATE include glfw/include imgui imgui/backends)

find_package(OpenGL REQUIRED)
target_link_libraries(MyApp ${OPENGL_LIBRARIES} glfw imgui)
