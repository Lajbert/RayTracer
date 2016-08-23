#pragma once
#include "Texture.h"
class UniformColorTexture : public Texture {
public:
	UniformColorTexture() {}
	UniformColorTexture(Vector3f color) : color(color) {}
	virtual Vector3f Value(float u, float v, const Vector3f& p) const;

private:
	Vector3f color;
};

