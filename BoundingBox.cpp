#include "BoundingBox.h"

BoundingBox::BoundingBox(const Vector3f a, const Vector3f b)
{
	min = a;
	max = b;
}

Vector3f BoundingBox::GetMin() const
{
	return min;
}

Vector3f BoundingBox::GetMax() const
{
	return max;
}

bool BoundingBox::Hit(const Ray& ray, float tmin, float tmax) const
{
	/*
	for (int i = 0; i < 3; i++) {
		float t0 = ffmin((min[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i], (max[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i]);
		float t1 = ffmax((min[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i], (max[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i]);
		tmin = ffmax(t0, tmin);
		tmax = ffmin(t1, tmax);
		if (tmax <= tmin) {
			return false;
		}
	}
	return true;
	*/
	for (int i = 0; i < 3; i++) {
		float invD = 1.0f / ray.GetDirection()[i];
		float t0 = (GetMin()[i] - ray.GetOrigin()[i]) * invD;
		float t1 = (GetMax()[i] - ray.GetOrigin()[i]) * invD;
		if (invD < 0.0f) {
			std::swap(t0, t1);
		}
		tmin = t0 > tmin ? t0 : tmin;
		tmax = t1 < tmax ? t1 : tmax;
		if (tmax <= tmin) {
			return false;
		}
	}
	return true;
}
