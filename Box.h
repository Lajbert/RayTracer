#pragma once
#ifndef BOXH
#define BOXH

#include "PhysicalObject.h"
#include "Rectangle.h"

class Box : public PhysicalObject {
private:
	Vector3f pMin;
	Vector3f pMax;

	PhysicalObject * planesList;

public:
	Box() {};
	Box(const Vector3f p0, const Vector3f p1, Material * material);
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const override;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;
};

#endif BOXH