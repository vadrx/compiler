cmake_minimum_required(VERSION 3.0.0)
project(compiler)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB sources
    "src/*.h"
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${sources})