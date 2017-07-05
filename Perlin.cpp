#include "Perlin.h"
#include "MathUtils.h"

Vector3f * Perlin::ranVec = PerlinGenerate();
int * Perlin::permX = PerlinGeneratePerm();
int * Perlin::permY = PerlinGeneratePerm();
int * Perlin::permZ = PerlinGeneratePerm();

void Perlin::Permute(int * p, int n)
{
	for (int i = n - 1; i > 0; i--) {
		int target = int(MathUtils::GetRandom() * (i + 1));
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

inline float Perlin::TrilinearInterpolate(float c[2][2][2], float u, float v, float w) const
{
	float accum = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				accum += (i * u + (1 - i) * (1 - u)) *
					(j * v + (1 - j) *  (1 - v)) *
					(k * w + (1 - k) * (1 - w)) *
					c[i][j][k];
			}
		}
	}

	return accum;
}

inline float Perlin::PerlinInterplate(Vector3f c[2][2][2], float u, float v, float w) const
{
	float uu = u * u * (3 - 2 * u);
	float vv = v * v * (3 - 2 * v);
	float ww = w * w * (3 - 2 * w);

	float accum = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				Vector3f weightVector(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu)) *
					(j * vv + (1 - j) *  (1 - vv)) *
					(k * ww + (1 - k) * (1 - ww)) *
					Scalar(c[i][j][k], weightVector);
			}
		}
	}

	return accum;
}

float Perlin::GenerateNoise(const Vector3f & p) const
{
	float u = p.x() - floor(p.x());
	float v = p.y() - floor(p.y());
	float w = p.z() - floor(p.z());
	int i = floor(p.x());
	int j = floor(p.y());
	int k = floor(p.z());

	Vector3f c[2][2][2];
	for (int di = 0; di < 2; di++) {
		for (int dj = 0; dj < 2; dj++) {
			for (int dk = 0; dk < 2; dk++) {
				c[di][dj][dk] = ranVec[permX[(i + di) & 255] ^ permY[(j + dj) & 255] ^ permZ[(k + dk) & 255]];
			}
		}
	}

	return PerlinInterplate(c, u, v, w);
}

Vector3f * Perlin::PerlinGenerate()
{
	Vector3f * p = new Vector3f[256];
	for (int i = 0; i < 256; i++) {
		p[i] = UnitVector(Vector3f(-1 + 2 * MathUtils::GetRandom(), -1 + 2 * MathUtils::GetRandom(), 
			-1 + 2 * MathUtils::GetRandom()));
	}
	return p;
}

int * Perlin::PerlinGeneratePerm()
{
	int * p = new int[256];
	for (int i = 0; i < 256; i++) {
		p[i] = i;
	}
	Permute(p, 256);
	return p;
}

float Perlin::Turbulence(const Vector3f & p, int depth) const
{
	float accum = 0;
	Vector3f tempP = p;
	float weight = 1.0;
	for (int i = 0; i < depth; i++) {
		accum += weight * GenerateNoise(tempP);
		weight *= 0.5;
		tempP *= 2;
	}
	return fabs(accum);
}
