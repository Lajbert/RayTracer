cmake_minimum_required(VERSION 3.6)
project(RayTracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Camera.cpp Camera.h Dialectric.cpp Dialectric.h Lambert.cpp Lambert.h Material.cpp Material.h MathUtils.cpp MathUtils.h Metal.cpp Metal.h PhysicalObjectList.cpp PhysicalObjectList.h PhysicalObject.cpp PhysicalObject.h Ray.cpp Ray.h Sphere.cpp Sphere.h Vector3f.cpp Vector3f.h)
add_executable(RayTracer ${SOURCE_FILES})