cmake_minimum_required(VERSION 3.6)
project(RayTracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Box.h Box.cpp BoundingBox.cpp BoundingBox.h BVHNode.cpp BVHNode.h CheckerTexture.cpp CheckerTexture.h DiffuseLight.cpp DiffuseLight.h MovingSphere.cpp MovingSphere.h NoiseTexture.cpp NoiseTexture.h NormalFlipper.cpp NormalFlipper.h Perlin.cpp Perlin.h RayTracerCore.cpp RayTracerCore.h Rectangle.cpp Rectangle.h Rotate.cpp Rotate.h Texture.cpp Texture.h Translate.cpp Translate.h UniformColorTexture.cpp UniformColorTexture.h main.cpp Camera.cpp Camera.h Dialectric.cpp Dialectric.h Lambert.cpp Lambert.h Material.cpp Material.h MathUtils.cpp MathUtils.h Metal.cpp Metal.h PhysicalObjectList.cpp PhysicalObjectList.h PhysicalObject.cpp PhysicalObject.h Ray.cpp Ray.h Sphere.cpp Sphere.h Vector3f.cpp Vector3f.h ImageTexture.h ImageTexture.cpp)
add_executable(RayTracer ${SOURCE_FILES} ImageTexture.h ImageTexture.cpp)