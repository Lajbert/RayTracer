#pragma once
#ifndef LAMBERTH
#define LAMBERTH

#include "Material.h"
#include "Texture.h"

class Lambert : public Material
{
private:
	Texture* texture;
public:
	Lambert(Texture* texture) : texture(texture) {}
	virtual bool Scatter(const Ray& incomingRay, const HitData& hitData, Vector3f& attenuation, Ray& scattered) const override;
};

#endif