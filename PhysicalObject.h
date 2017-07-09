#pragma once
#ifndef PHYSICALOBJECTH
#define PHYSICALOBJECTH

#include "Ray.h"
#include "Material.h"
#include "BoundingBox.h"

class Material;

struct HitData{
	float t;
	Vector3f hitPoint;
	Vector3f normal;
	Material* material;

	float u;
	float v;

};

class PhysicalObject
{
public:
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const = 0;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const = 0;
};

#endif