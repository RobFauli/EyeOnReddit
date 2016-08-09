cmake_minimum_required(VERSION 3.2.2)
project(PhysicsSandbox)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi -pedantic")
set(CMAKE_CXX_STANDARD 14)

include_directories(src/backend)

# Program source code
add_subdirectory(src)

# Test code and google test library
add_subdirectory(unittests)
