#pragma once
#ifndef BVHNODEH
#define BVHNODEH

#include "PhysicalObject.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "PhysicalObject.h"

class BVHNode : public PhysicalObject {
private:
	PhysicalObject * leftChild;
	PhysicalObject * rightChild;
	BoundingBox boundingBox;

	//static int compareBoxesX(const void * a, const void * b);

public:
	BVHNode() {}
	BVHNode(PhysicalObject ** list, int n, float startTime, float endTime);
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const override;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;
};

#endif