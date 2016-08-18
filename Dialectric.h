#pragma once
#ifndef DIALECTRICH
#define DIALECTRICH
#include "Material.h"

class Dialectric : public Material
{
private:
	float indexOfRefraction;
	Vector3f attenuation = Vector3f(1.0, 1.0, 1.0);
public:
	Dialectric(float indexOfRefraction) : indexOfRefraction(indexOfRefraction) {}
	Dialectric(float indexOfRefraction, Vector3f attenuation) : indexOfRefraction(indexOfRefraction), attenuation(attenuation) {}
	virtual bool Scatter(const Ray& incomingRay, const HitData& hitData, Vector3f& attenuation, Ray& scattered) const override;
	bool Refract(const Vector3f& v, const Vector3f& n, float ni_over_nt, Vector3f& refracted) const;
};
#endif
