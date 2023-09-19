########### BOILER PLATE #############
# Set toplevel project & cmake version
cmake_minimum_required(VERSION 3.16)
project(MyApp LANGUAGES CXX)

# Set C++ standartd
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
########### BOILER PLATE #############

# Add GLFW dependency as subproject
set(GLFW_BUILD_DOCS OFF)    
set(GLFW_BUILD_TESTS OFF)    
set(GLFW_BUILD_EXAMPLES OFF)    
add_subdirectory(vendor/glfw)
# Add ImGUI dependency as subproject
add_subdirectory(vendor/imgui)

# Add project sources
file(GLOB SOURCES src/*.cpp)
# Add ImGui GLFW/OpenGL backends to sources
set(SOURCES ${SOURCES}
    vendor/imgui/backends/imgui_impl_opengl3.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp)

# Add project headers
file(GLOB HEADERS include/*.hpp)

# Build target & include locations
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    include
    vendor/glfw/include
    vendor/imgui
    vendor/imgui/backends)

# Build target link dependencies
find_package(OpenGL REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    glfw
    imgui)
