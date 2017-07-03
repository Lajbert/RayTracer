#pragma once
#ifndef NOISETEXTUREH
#define NOISETEXTUREH

#include "Texture.h"
#include "Perlin.h"

class NoiseTexture : public Texture {
private:
	Perlin noise;

	float scale;

public:
	NoiseTexture() {}
	NoiseTexture(float scale) : scale(scale) {}
	virtual Vector3f Value(float u, float v, const Vector3f& p) const override;
};

#endif