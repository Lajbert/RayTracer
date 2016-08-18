#include "Dialectric.h"
#include "MathUtils.h"


bool Dialectric::Refract(const Vector3f & v, const Vector3f & n, float ni_over_nt, Vector3f& refracted) const
{
	Vector3f unitVector = UnitVector(v);
	float dotProduct = Scalar(unitVector, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dotProduct * dotProduct);

	if (discriminant > 0) {
		refracted = ni_over_nt * (unitVector - n * dotProduct) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

bool Dialectric::Scatter(const Ray & incomingRay, const HitData & hitData, Vector3f & attenuation, Ray & scattered) const
{
	Vector3f outwardNormal;
	Vector3f reflected = Reflect(incomingRay.GetDirection(), hitData.normal);
	float ni_over_nt;
	attenuation = this->attenuation;
	Vector3f refracted;
	float reflectProb;
	float cosine;
	if (Scalar(incomingRay.GetDirection(), hitData.normal) > 0) {
		outwardNormal = -hitData.normal;
		ni_over_nt = indexOfRefraction;
		cosine = indexOfRefraction * Scalar(incomingRay.GetDirection(), hitData.normal) / incomingRay.GetDirection().GetLength();
	} else {
		outwardNormal = hitData.normal;
		ni_over_nt = 1.0 / indexOfRefraction;
		cosine = -Scalar(incomingRay.GetDirection(), hitData.normal) / incomingRay.GetDirection().GetLength();
	}

	if (Refract(incomingRay.GetDirection(), outwardNormal, ni_over_nt, refracted)) {
		reflectProb = Schlick(cosine, indexOfRefraction);
	} else {
		reflectProb = 1.0;
	}

	if (MathUtils::GetRandom() < reflectProb) {
		scattered = Ray(hitData.hitPoint, reflected);
	}
	else {
		scattered = Ray(hitData.hitPoint, refracted);
	}

	return true;
}
