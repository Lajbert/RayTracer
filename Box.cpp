#include "Box.h"
#include "NormalFlipper.h"
#include "PhysicalObjectList.h"

Box::Box(const Vector3f p0, const Vector3f p1, Material * material)
{
	pMin = p0;
	pMax = p1;
	PhysicalObject ** planes = new PhysicalObject*[6];
	planes[0] = new XYRectangle(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), material);
	planes[1] = new NormalFlipper(new XYRectangle(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), material));
	planes[2] = new XZRectangle(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), material);
	planes[3] = new NormalFlipper(new XZRectangle(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), material));
	planes[4] = new YZRectangle(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), material);
	planes[5] = new NormalFlipper(new YZRectangle(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), material));
	planesList = new PhysicalObjectList(planes, 6);
}

bool Box::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & data) const
{
	return planesList->Hit(ray, minTolerance, maxTolerance, data);
}

bool Box::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	box = BoundingBox(pMin, pMax);
	return true;
}
