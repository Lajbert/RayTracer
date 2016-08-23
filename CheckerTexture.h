#pragma once
#include "Texture.h"

class CheckerTexture : public Texture {
public:
	CheckerTexture() {}
	CheckerTexture(Texture* texture0, Texture* texture1) : even(texture0), odd(texture1) {}
	virtual Vector3f Value(float u, float v, const Vector3f& p) const;
private:
	Texture* even;
	Texture* odd;
};

