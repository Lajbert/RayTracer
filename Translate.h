#pragma once
#ifndef TRANSLATEH
#define TRANSLATEH

#include "PhysicalObject.h"

class Translate : public PhysicalObject {
private:
	Vector3f offset;
	PhysicalObject * object;

public:
	Translate(PhysicalObject * object, const Vector3f & displacement) : object(object), offset(displacement) {};
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const override;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;
};

#endif TRANSLATEH