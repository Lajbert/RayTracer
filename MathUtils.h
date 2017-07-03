#pragma once
#ifndef MATHUTILSH
#define MATHUTILSH
#include "Vector3f.h"
#include "BoundingBox.h"

class MathUtils
{
public:
	/*
	Returns a random point in a unit length sphere. Works based on rejection: generating a random point in a unit cube and if is in the sphere as well, we are okay, otherwise we generate again.
	*/
	static inline Vector3f RandomInUnitSphere() {
		Vector3f point;

		do {
			point = 2.0 * Vector3f(GetRandom(), GetRandom(), GetRandom()) - Vector3f(1, 1, 1);
		} while (point.GetSquaredLength() >= 1.0);

		return point;
	}

	/*
	Returns a random number r where 0 <= r < 1
	*/
	static inline float GetRandom() {
		return ((float)rand() / RAND_MAX);
	}

	static inline BoundingBox GetSurroundingBox(BoundingBox box0, BoundingBox box1)
	{
		Vector3f small(fmin(box0.GetMin().x(), box1.GetMin().x()),
			fmin(box0.GetMin().y(), box1.GetMin().y()),
			fmin(box0.GetMin().z(), box1.GetMin().z()));
		Vector3f big(fmax(box0.GetMax().x(), box1.GetMax().x()),
			fmax(box0.GetMax().y(), box1.GetMax().y()),
			fmax(box0.GetMax().z(), box1.GetMax().z()));

		return BoundingBox(small, big);
	}
};

#endif