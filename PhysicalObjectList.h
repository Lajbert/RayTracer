#pragma once
#ifndef PHYSICALOBJECTLISTH
#define PHYSICALOBJECTLISTH

#include "PhysicalObject.h"

class PhysicalObjectList : public PhysicalObject
{
private:
	PhysicalObject** list;
	int size;

public:
	PhysicalObjectList() {}
	PhysicalObjectList(PhysicalObject** list, int size);
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& hitData) const override;

	/* Generates a big, more or less random scene.*/
	static PhysicalObject *RandomScene();
	/* Returns a small, static scene. */
	static PhysicalObject *SmallScene();
};

#endif