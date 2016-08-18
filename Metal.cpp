#include "Metal.h"

bool Metal::Scatter(const Ray& incomingRay, const HitData & hitData, Vector3f& attenuation, Ray & scattered) const
{
	Vector3f reflected = Reflect(UnitVector(incomingRay.GetDirection()), hitData.normal);
	scattered = Ray(hitData.hitPoint, reflected + fuzziness * MathUtils::RandomInUnitSphere());
	attenuation = albedo;
	return (Scalar(scattered.GetDirection(), hitData.normal) > 0);
}
