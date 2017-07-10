#include "Rotate.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

YRotate::YRotate(PhysicalObject * object, float angle)
{
	this->object = object;
	float angleRad = (M_PI / 180.0) * angle;
	sinTheta = sin(angleRad);
	cosTheta = cos(angleRad);
	hasBoundingBox = object->BoundingBoxHit(0, 1, boundingBox);

	Vector3f min(FLT_MAX, FLT_MAX, FLT_MAX);
	Vector3f max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				float x = i + boundingBox.GetMax().x() + (1 - i) * boundingBox.GetMin().x();
				float y = j + boundingBox.GetMax().y() + (1 - j) * boundingBox.GetMin().y();
				float z = k + boundingBox.GetMax().z() + (1 - k) * boundingBox.GetMin().z();

				float newX = cosTheta * x + sinTheta * z;
				float newZ = -sinTheta * x + cosTheta * z;
				Vector3f test(newX, y, newZ);
				for (int c = 0; c < 3; c++) {
					if (test[c] > max[c]) {
						max[c] = test[c];
					}
					if (test[c] < min[c]) {
						min[c] = test[c];
					}
				}
			}
		}
	}
	boundingBox = BoundingBox(min, max);
}

bool YRotate::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & data) const
{
	Vector3f origin = ray.GetOrigin();
	Vector3f direction = ray.GetDirection();
	origin[0] = cosTheta * ray.GetOrigin()[0] - sinTheta * ray.GetOrigin()[2];
	origin[2] = sinTheta * ray.GetOrigin()[0] + cosTheta * ray.GetOrigin()[2];
	direction[0] = cosTheta * ray.GetDirection()[0] - sinTheta * ray.GetDirection()[2];
	direction[2] = sinTheta * ray.GetDirection()[0] + cosTheta * ray.GetDirection()[2];

	Ray rotated(origin, direction, ray.GetTime());
	
	if (object->Hit(rotated, minTolerance, maxTolerance, data)) {
		Vector3f newHitPoint = data.hitPoint;
		Vector3f newNormal = data.normal;

		newHitPoint[0] = cosTheta * data.hitPoint[0] + sinTheta * data.hitPoint[2];
		newHitPoint[2] = -sinTheta * data.hitPoint[0] + cosTheta * data.hitPoint[2];

		newNormal[0] = cosTheta * data.normal[0] + sinTheta * data.normal[2];
		newNormal[2] = -sinTheta * data.normal[0] + cosTheta * data.normal[2];

		data.hitPoint = newHitPoint;
		data.normal = newNormal;
		return true;
	}
	return false;
}

bool YRotate::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	box = boundingBox;
	return hasBoundingBox;
}
