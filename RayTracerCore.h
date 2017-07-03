#pragma once
#ifndef RAYTRACERCOREH
#define RAYTRACERCOREH
#include "Vector3f.h"
#include "Ray.h"
#include "PhysicalObject.h"
#include "Camera.h"

class RayTracerCore {

private:

	int numberOfSamples;
	PhysicalObject* scene;
	Camera* camera;

	Vector3f Color(const Ray& ray, PhysicalObject *scene, int depth);

public:
	RayTracerCore(int numberOfSamples, PhysicalObject* scene, Camera* camera);

	Vector3f RayTrace(int row, PhysicalObject* scene, Camera camera);


};
#endif