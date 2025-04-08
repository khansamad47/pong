cmake_minimum_required(VERSION 3.10)

project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include headers from src/
include_directories(src)

# Gather source files from src/
file(GLOB SOURCES src/*.cpp)

add_executable(pong ${SOURCES})

target_link_libraries(pong PRIVATE SDL2)
