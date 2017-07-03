#pragma once
#ifndef PERLINH
#define PERLINH

#include "Vector3f.h"

class Perlin {

private:
	static Vector3f * ranVec;
	static int * permX;
	static int * permY;
	static int * permZ;

	static void Permute(int * p, int n);

	inline float TrilinearInterpolate(float c[2][2][2], float u, float v, float w) const;
	inline float PerlinInterplate(Vector3f c[2][2][2], float u, float v, float w) const;
public:
	float GenerateNoise(const Vector3f & p) const;
	static Vector3f * PerlinGenerate();
	static int* PerlinGeneratePerm();
};

#endif