#pragma once
#ifndef RAYH
#define RAYH
#include "Vector3f.h"
class Ray
{
private:
	Vector3f origin;
	Vector3f direction;
	float time;

public:

	Ray() {}

	Ray(const Vector3f& origin, const Vector3f& direction, float time = 0.0);

	Vector3f GetOrigin() const;

	Vector3f GetDirection() const;

	Vector3f GetPointAtParameter(float t) const;

	float GetTime() const;
};
#endif

