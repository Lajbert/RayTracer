#pragma once
#ifndef MOVINGSPHEREH
#define MOVINGSPHEREH

#include "PhysicalObject.h"
#include "Material.h"
#include "Vector3f.h"

class MovingSphere : public PhysicalObject {

private:
	Vector3f centerStart;
	Vector3f centerEnd;
	float startTime;
	float endTime;
	float radius;

	Material *material;

public:
	MovingSphere() {}
	MovingSphere(Vector3f centerStart, Vector3f centerEnd, float startTime, float endTime, float radius, Material *material) 
		: centerStart(centerStart), centerEnd(centerEnd), startTime(startTime), endTime(endTime), radius(radius), material(material) {};
	virtual bool Hit(const Ray& r, float tmin, float tmax, HitData& hitData) const;
	Vector3f Center(float time) const;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;
};

#endif