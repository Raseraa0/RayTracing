cmake_minimum_required(VERSION 3.0)

project(RayTracing)

set(SOURCES
    src/color.cpp
    src/interval.cpp
    src/main.cpp
)

set(HEADERS
    include/camera.h
    include/color.h
    include/hittable.h
    include/hittable_list.h
    include/interval.h
    include/ray.h
    include/sphere.h
    include/utils.h
    include/vec3.h
)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_executable(raytracing ${SOURCES} ${HEADERS})
