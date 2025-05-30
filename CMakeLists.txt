cmake_minimum_required(VERSION 3.22)

project(RayTracing)

file(
  GLOB
  SOURCES
  "src/*.cpp"
  "src/Hittable/*.cpp"
  "src/Material/*.cpp"
  "src/Utilities/*.cpp"
  "src/Texture/*.cpp"
  "src/Scenes/*.cpp"
)

file(
  GLOB
  HEADERS
  "include/*.h"
  "include/Hittable/*.h"
  "include/Material/*.h"
  "include/Utilities/*.h"
  "include/Texture/*.h"
  "include/Scenes/*.h"
)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_compile_options(-O3)
add_compile_options(-flto)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wpedantic)
add_compile_options(-Werror)
add_compile_options(-Wconversion)
add_compile_options(-Wsign-conversion)
add_compile_options(-Wshadow)
add_compile_options(-Wnon-virtual-dtor)
add_compile_options(-Wreorder)
add_compile_options(-Wmaybe-uninitialized)
add_compile_options(-Wunused-variable)

add_executable(
  raytracing
  ${SOURCES}
  ${HEADERS}
)

target_include_directories(raytracing PRIVATE include)
