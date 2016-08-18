#pragma once
#ifndef LAMBERTH
#define LAMBERTH

#include "Material.h"

class Lambert : public Material
{
private:
	Vector3f albedo;
public:
	Lambert(const Vector3f& albedo) : albedo(albedo) {}
	virtual bool Scatter(const Ray& incomingRay, const HitData& hitData, Vector3f& attenuation, Ray& scattered) const override;
};

#endif