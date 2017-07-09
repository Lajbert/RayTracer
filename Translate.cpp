#include "Translate.h"

bool Translate::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & data) const
{
	Ray movedRay(ray.GetOrigin() - offset, ray.GetDirection(), ray.GetTime());
	if (object->Hit(movedRay, minTolerance, maxTolerance, data)) {
		data.hitPoint += offset;
		return true;
	}
	return false;
}

bool Translate::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	if (object->BoundingBoxHit(startTime, endTime, box)) {
		box = BoundingBox(box.GetMin() + offset, box.GetMax() + offset);
		return true;
	}
	return false;
}
