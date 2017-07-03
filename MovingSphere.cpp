#include "MovingSphere.h"
#include "MathUtils.h"

bool MovingSphere::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & hitData) const
{
	Vector3f distance = ray.GetOrigin() - Center(ray.GetTime());
	float a = Scalar(ray.GetDirection(), ray.GetDirection());
	float b = Scalar(distance, ray.GetDirection());
	float c = Scalar(distance, distance) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {

		float tmp = (-b - sqrt(b * b - a * c)) / a;

		if (tmp < maxTolerance && tmp > minTolerance) {
			hitData.t = tmp;
			hitData.hitPoint = ray.GetPointAtParameter(hitData.t);
			hitData.normal = (hitData.hitPoint - Center(ray.GetTime())) / radius;
			hitData.material = material;
			return true;
		}

		tmp = (-b + sqrt(b * b - a * c)) / a;

		if (tmp < maxTolerance && tmp > minTolerance) {
			hitData.t = tmp;
			hitData.hitPoint = ray.GetPointAtParameter(hitData.t);
			hitData.normal = (hitData.hitPoint - Center(ray.GetTime())) / radius;
			hitData.material = material;
			return true;
		}
	}
	return false;
}

Vector3f MovingSphere::Center(float time) const
{
	return centerStart + ((time - startTime) / (endTime - startTime)) * (centerEnd - centerStart);
}


bool MovingSphere::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	BoundingBox box0(Center(startTime) - Vector3f(radius, radius, radius), Center(startTime) + Vector3f(radius, radius, radius));
	BoundingBox box1(Center(endTime) - Vector3f(radius, radius, radius), Center(endTime) + Vector3f(radius, radius, radius));
	box = MathUtils::GetSurroundingBox(box0, box1);
	return true;
}
