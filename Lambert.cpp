#include "Lambert.h"
#include "MathUtils.h"

bool Lambert::Scatter(const Ray& incomingRay, const HitData& hitData, Vector3f& attenuation, Ray & scattered) const
{
	Vector3f target = hitData.hitPoint + hitData.normal + MathUtils::RandomInUnitSphere();
	scattered = Ray(hitData.hitPoint, target - hitData.hitPoint);
	attenuation = texture->Value(0, 0, hitData.hitPoint);
	return true;
}
