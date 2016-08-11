#include "Material.h"

Vector3f Material::Reflect(const Vector3f& v, const Vector3f n) const
{
	return v - 2 * Scalar(v, n) * n;
}

float Material::Schlick(float cosine, float indexOfRefraction) const
{
	float r0 = (1 - indexOfRefraction) / (1 + indexOfRefraction);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
