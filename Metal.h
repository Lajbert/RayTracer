#pragma once
#ifndef METALH
#define METALH

#include "Vector3f.h"
#include "Ray.h"
#include "PhysicalObject.h"
#include "Material.h"
#include "MathUtils.h"

class Metal : public Material
{
private:
	Vector3f albedo;
public:
	Metal(const Vector3f& albedo, float fuzziness) : albedo(albedo) {
		this->fuzziness = fuzziness;
	}
	virtual bool Scatter(const Ray& incomingRay, const HitData& hitData, Vector3f& attenuation, Ray& scattered) const override;
};

#endif