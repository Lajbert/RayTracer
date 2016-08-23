#include "CheckerTexture.h"

Vector3f CheckerTexture::Value(float u, float v, const Vector3f & p) const {
	float sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
	if (sines < 0) {
		return odd->Value(u, v, p);
	} else {
		return even->Value(u, v, p);
	}
}
