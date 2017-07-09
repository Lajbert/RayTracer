#pragma once
#ifndef NORMALFLIPPERH
#define NORMALFLIPPERH

#include "PhysicalObject.h"
class NormalFlipper : public PhysicalObject {
private:
	PhysicalObject * object;

public:
	NormalFlipper(PhysicalObject * object) : object(object) {};
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const override;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;
};

#endif NORMALFLIPPERH