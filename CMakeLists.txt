cmake_minimum_required(VERSION 3.0)
project(FractalExplorer)

set (CMAKE_CXX_STANDARD 11)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libraries/glfw)

include_directories(libraries/glad/include/ libraries/glfw/include/ headers/)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS headers/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} libraries/glad/src/glad.c)

target_link_libraries(${PROJECT_NAME} glfw)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
