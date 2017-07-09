#pragma once;
#ifndef RECTANGLEH
#define RECTANGLEH

#include "PhysicalObject.h"

class XYRectangle : public PhysicalObject {

private:
	float x0;
	float x1;
	float y0;
	float y1;
	float k;

	Material * material;

public:
	XYRectangle() {};
	XYRectangle(float x0, float x1, float y0, float y1, float k, Material * material) : x0(x0), x1(x1), y0(y0), y1(y1), k(k), material(material) {};
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;
	
};

class XZRectangle : public PhysicalObject {

private:
	float x0;
	float x1;
	float z0;
	float z1;
	float k;

	Material * material;

public:
	XZRectangle() {};
	XZRectangle(float x0, float x1, float z0, float z1, float k, Material * material) : x0(x0), x1(x1), z0(z0), z1(z1), k(k), material(material) {};
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;

};

class YZRectangle : public PhysicalObject {

private:
	float y0;
	float y1;
	float z0;
	float z1;
	float k;

	Material * material;

public:
	YZRectangle() {};
	YZRectangle(float y0, float y1, float z0, float z1, float k, Material * material) : z0(z0), z1(z1), y0(y0), y1(y1), k(k), material(material) {};
	virtual bool Hit(const Ray& ray, float minTolerance, float maxTolerance, HitData& data) const;
	virtual bool BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const override;

};

#endif RECTANGLEH