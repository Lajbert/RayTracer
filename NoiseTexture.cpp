#include "NoiseTexture.h"

static int i = 0;

Vector3f NoiseTexture::Value(float u, float v, const Vector3f & p) const
{
	return Vector3f(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.Turbulence(p)));
}
