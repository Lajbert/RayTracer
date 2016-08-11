#include "Sphere.h"

/*
For sphere s(cx, cy, cz) and point p(x,y,z), if:
(x-cy)^2 + (y-cy)^2 + (z-cz)^2 = R^2
then p is on the sphere, otherwise not.
To determine whether the ray hit the sphere or not, we use the simple high school quadratic formula.
No solution: the ray does not hit the sphere.
One real solution: the ray touches the sphere
Two real solutions: the ray goes (or could go) through the sphere
*/
bool Sphere::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData& hitData) const
{
	Vector3f distance = ray.GetOrigin() - center;
	float a = Scalar(ray.GetDirection(), ray.GetDirection());
	float b = Scalar(distance, ray.GetDirection());
	float c = Scalar(distance, distance) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {

		float tmp = (-b - sqrt(b * b - a * c)) / a;

		if(tmp < maxTolerance && tmp > minTolerance) {
			hitData.t = tmp;
			hitData.hitPoint = ray.GetPointAtParameter(hitData.t);
			hitData.normal = (hitData.hitPoint - center) / radius;
			hitData.material = material;
			return true;
		}

		tmp = (-b + sqrt(b * b - a * c)) / a;

		if (tmp < maxTolerance && tmp > minTolerance) {
			hitData.t = tmp;
			hitData.hitPoint = ray.GetPointAtParameter(hitData.t);
			hitData.normal = (hitData.hitPoint - center) / radius;
			hitData.material = material;
			return true;
		}
	}
	return false;
	
}