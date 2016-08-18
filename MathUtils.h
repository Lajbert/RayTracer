#pragma once
#ifndef MATHUTILSH
#define MATHUTILSH
#include "Vector3f.h"
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
};

#endif