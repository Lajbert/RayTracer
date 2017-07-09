#include "DiffuseLight.h"

bool DiffuseLight::Scatter(const Ray & incomingRay, const HitData & hitData, Vector3f & attenuation, Ray & scattered) const
{
	return false;
}

Vector3f DiffuseLight::GetEmitted(float u, float v, Vector3f & p) const
{
	return emission->Value(u, v, p);
}
