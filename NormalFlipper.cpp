#include "NormalFlipper.h"

bool NormalFlipper::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & data) const
{
	if (object -> Hit(ray, minTolerance, maxTolerance, data)) {
		data.normal -= data.normal;
		return true;
	}
	return false;
}

bool NormalFlipper::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	return object->BoundingBoxHit(startTime, endTime, box);
}
