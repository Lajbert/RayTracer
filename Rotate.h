#pragma once
#ifndef ROTATEH
#define ROTATEH

#include "PhysicalObject.h"

class YRotate : public PhysicalObject {
private:
	PhysicalObject * object;
	float sinTheta;
	float cosTheta;
	bool hasBoundingBox;
	BoundingBox boundingBox;

public:
	YRotate(PhysicalObject * object, float angle);
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const override;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;
};

#endif
