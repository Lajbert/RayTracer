#pragma once
#ifndef PHYSICALOBJECTH
#define PHYSICALOBJECTH

#include "Ray.h"
#include "Material.h"

class Material;

struct HitData{
	float t;
	Vector3f hitPoint;
	Vector3f normal;
	Material* material;
};

class PhysicalObject
{
public:
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const = 0;
};

#endif