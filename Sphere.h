#pragma once
#ifndef SPHEREH
#define SPHEREH

#include "PhysicalObject.h"
#include "Vector3f.h"
#include "Material.h"

class Sphere : public PhysicalObject
{
private:
	Vector3f center;
	float radius;
	Material* material;
public:
	Sphere(Vector3f center, float radius, Material* material) : center(center), radius(radius), material(material) {}
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& hitData) const override;

};

#endif