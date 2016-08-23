#include "UniformColorTexture.h"

Vector3f UniformColorTexture::Value(float u, float v, const Vector3f & p) const {
	return color;
}
