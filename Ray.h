#pragma once
#ifndef RAYH
#define RAYH
#include "Vector3f.h"
class Ray
{
private:
	Vector3f origin;
	Vector3f direction;

public:

	Ray() {}

	Ray(const Vector3f& origin, const Vector3f& direction);

	Vector3f GetOrigin() const;

	Vector3f GetDirection() const;

	Vector3f GetPointAtParameter(float t) const;

};
#endif

