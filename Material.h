#pragma once
#ifndef MATERIALH
#define MATERIALH

#include "Ray.h"
#include "PhysicalObject.h"

class HitData;

class Material
{	
protected:
	float fuzziness;
public:
	virtual bool Scatter(const Ray& incomingRay, const HitData& hitData, Vector3f& attenuation, Ray& scattered) const = 0;
	virtual Vector3f GetEmitted(float u, float v, Vector3f & p) const { return Vector3f(0.0, 0.0, 0.0); };
	Vector3f Reflect(const Vector3f& v, const Vector3f n) const;
	float Schlick(float cosine, float indexOfRefraction) const;
};
#endif