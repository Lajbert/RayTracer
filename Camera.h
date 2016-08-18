#pragma once
#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"
#include "Vector3f.h"

class Camera
{
private:
	Vector3f lowerLeftCorner;
	Vector3f horizontal;
	Vector3f vertical;
	Vector3f origin;
	float lensRadius;
	Vector3f u, v, w;
public:
	Camera(Vector3f lookFrom, Vector3f lookAt, Vector3f viewUp, float fieldOfView, float aspect, float aperture, float focusDistance);
	Ray GetRay(float u, float v);
	Vector3f RandomInUnitDisk();
};

#endif