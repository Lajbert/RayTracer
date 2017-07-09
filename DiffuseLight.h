#pragma once
#ifndef DIFFUSELIGHTH
#define DIFFUSELIGHTH

#include "Material.h"
#include "Texture.h"

class DiffuseLight : public Material {

private:
	Texture * emission;

public:
	DiffuseLight(Texture * emission) : emission(emission) {};
	virtual bool Scatter(const Ray& incomingRay, const HitData& hitData, Vector3f& attenuation, Ray& scattered) const override;
	virtual Vector3f GetEmitted(float u, float v, Vector3f & p) const override;

};

#endif DIFFUSELIGHTH
