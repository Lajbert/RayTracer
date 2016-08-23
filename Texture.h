#pragma once
#include "Vector3f.h"

class Texture
{
public:
	virtual Vector3f Value(float u, float v, const Vector3f& p) const = 0;
};

