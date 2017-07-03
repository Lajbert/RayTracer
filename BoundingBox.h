#pragma once
#ifndef BOUNDINGBOXH
#define BOUNDINGBOXH

#include "Vector3f.h"
#include "Ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class BoundingBox {

private:
	Vector3f min;
	Vector3f max;

public:
	BoundingBox() {}
	BoundingBox(const Vector3f a, const Vector3f b);

	Vector3f GetMin() const;
	Vector3f GetMax() const;

	bool Hit(const Ray& ray, float tmin, float tmax) const;

};

#endif