#include "Ray.h"

Ray::Ray(const Vector3f & origin, const Vector3f & direction, float time)
{
	this->origin = origin;
	this->direction = direction;
	this->time = time;
}

Vector3f Ray::GetOrigin() const
{
	return origin;
}

Vector3f Ray::GetDirection() const
{
	return direction;
}

Vector3f Ray::GetPointAtParameter(float t) const
{
	return origin + t * direction;
}

float Ray::GetTime() const
{
	return time;
}
