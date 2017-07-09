#include "Rectangle.h"

// XY rectangle ------------------
bool XYRectangle::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & data) const
{
	float t = (k - ray.GetOrigin().z()) / ray.GetDirection().z();
	if (t < minTolerance || t > maxTolerance) {
		return false;
	}
	float x = ray.GetOrigin().x() + t * ray.GetDirection().x();
	float y = ray.GetOrigin().y() + t * ray.GetDirection().y();
	if (x < x0 || x > x1 || y < y0 || y > y1) {
		return false;
	}
	data.u = (x - x0) / (x1 - x0);
	data.v = (y - y0) / (y1 - y0);
	data.t = t;
	data.material = material;
	data.hitPoint = ray.GetPointAtParameter(t);
	data.normal = Vector3f(0, 0, 1);
	return true;
}

bool XYRectangle::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	box = BoundingBox(Vector3f(x0, y0, k - 0.0001), Vector3f(x1, y1, k + 0.0001));
	return true;
}

// XZ rectangle ------------------
bool XZRectangle::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & data) const
{
	float t = (k - ray.GetOrigin().y()) / ray.GetDirection().y();
	if (t < minTolerance || t > maxTolerance) {
		return false;
	}
	float x = ray.GetOrigin().x() + t * ray.GetDirection().x();
	float z = ray.GetOrigin().z() + t * ray.GetDirection().z();
	if (x < x0 || x > x1 || z < z0 || z > z1) {
		return false;
	}
	data.u = (x - x0) / (x1 - x0);
	data.v = (z - z0) / (z1 - z0);
	data.t = t;
	data.material = material;
	data.hitPoint = ray.GetPointAtParameter(t);
	data.normal = Vector3f(0, 1, 0);
	return true;
}

bool XZRectangle::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	box = BoundingBox(Vector3f(x0, k - 0.0001, z0), Vector3f(x1, k + 0.0001, z1));
	return true;
}


// YZ rectangle ------------------
bool YZRectangle::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & data) const
{
	float t = (k - ray.GetOrigin().x()) / ray.GetDirection().x();
	if (t < minTolerance || t > maxTolerance) {
		return false;
	}
	float y = ray.GetOrigin().y() + t * ray.GetDirection().y();
	float z = ray.GetOrigin().z() + t * ray.GetDirection().z();
	if (y < y0 || y > y1 || z < z0 || z > z1) {
		return false;
	}
	data.u = (y - y0) / (y1 - y0);
	data.v = (z - z0) / (z1 - z0);
	data.t = t;
	data.material = material;
	data.hitPoint = ray.GetPointAtParameter(t);
	data.normal = Vector3f(1, 0, 0);
	return true;
}

bool YZRectangle::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	box = BoundingBox(Vector3f(k - 0.0001, y0, z0), Vector3f(k + 0.0001, y1, z1));
	return true;
}
