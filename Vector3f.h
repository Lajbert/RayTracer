#pragma once

#ifndef VECTOR3FH
#define VECTOR3FH

#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/*
 A simple class for representing a 3D vector with floats.
 As it is going to be used for calculations, we heavily rely on operator overloading.
 We can think about the points of the vector as coordinates in 3D space or values for RGB color space.
 Very basic mathematchical knowledge of vectors is required to understand the implementation.
*/
class Vector3f
{

public:

	Vector3f() {}

	float e[3];

	Vector3f(float e0, float e1, float e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	// mapping the values to 3D space
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }

	// mapping the values to RGB color space
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const Vector3f& operator+() const { return *this; }

	inline Vector3f operator-() const {
		return Vector3f(-e[0], -e[1], -e[2]);
	}

	inline const float operator[] (int i) const { return e[i]; }
	inline float& operator[] (int i) { return e[i]; }

	inline Vector3f& operator+= (const Vector3f &vector2);
	inline Vector3f& operator-= (const Vector3f &vector2);
	inline Vector3f& operator*= (const Vector3f &vector2);
	inline Vector3f& operator/= (const Vector3f &vector2);
	inline Vector3f& operator*= (const float t);
	inline Vector3f& operator/= (const float t);

	// length of a 3D vector = sqrt(a^2 + b^2 + c^2)
	inline float GetLength() const {
		return sqrt( e[0] * e[0] + e[1] * e[1] + e[2] * e[2] );
	}

	//we don't always need the square root and thus save some performance, e.g. when comparing two vectors to see which one is longer
	inline float GetSquaredLength() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void MakeUnitVector();

};

inline void Vector3f::MakeUnitVector() {
	float k = 1.0 / GetLength();
	e[0] *= k; e[1] *= k; e[2] *= k;
}

inline istream& operator >> (istream &is, Vector3f &t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline ostream& operator<<(ostream &os, const Vector3f &t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline Vector3f operator+(const Vector3f &v1, const Vector3f &v2) {
	return Vector3f(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vector3f operator-(const Vector3f &v1, const Vector3f &v2) {
	return Vector3f(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vector3f operator*(const Vector3f &v1, const Vector3f &v2) {
	return Vector3f(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vector3f operator/(const Vector3f &v1, const Vector3f &v2) {
	return Vector3f(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vector3f operator*(float t, const Vector3f &v) {
	return Vector3f(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vector3f operator/(Vector3f v, float t) {
	return Vector3f(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline Vector3f operator*(const Vector3f &v, float t) {
	return Vector3f(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline float Scalar(const Vector3f &v1, const Vector3f &v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vector3f cross(const Vector3f &v1, const Vector3f &v2) {
	return Vector3f((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}


inline Vector3f& Vector3f::operator+=(const Vector3f &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

inline Vector3f& Vector3f::operator*=(const Vector3f &v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

inline Vector3f& Vector3f::operator/=(const Vector3f &v) {
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

inline Vector3f& Vector3f::operator-=(const Vector3f& v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

inline Vector3f& Vector3f::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline Vector3f& Vector3f::operator/=(const float t) {
	float k = 1.0 / t;

	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

inline Vector3f UnitVector(Vector3f v) {
	return v / v.GetLength();
}

#endif