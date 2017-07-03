#include "NoiseTexture.h"

Vector3f NoiseTexture::Value(float u, float v, const Vector3f & p) const
{
	return Vector3f(1, 1, 1) * noise.GenerateNoise(scale * p);
}
