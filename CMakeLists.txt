cmake_minimum_required(VERSION 3.0)

project(RayTracing)

file(
  GLOB
  SOURCES
  "src/*.cpp"
)

file(
  GLOB
  HEADERS
  "include/*.h"
)

set(CMAKE_CXX_FLAGS
    "-O3 -Wall -Wextra -Werror -Wpedantic -Wconversion -Wsign-conversion -Wshadow"
)

add_executable(
  raytracing
  ${SOURCES}
  ${HEADERS}
)
