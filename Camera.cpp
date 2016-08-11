#include "Camera.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "MathUtils.h"

Camera::Camera(Vector3f lookFrom, Vector3f lookAt, Vector3f viewUp, float fieldOfView, float aspect, float aperture, float focusDistance)
{
	lensRadius = aperture / 2;
	float theta = fieldOfView * M_PI / 180;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;

	origin = lookFrom;

	w = UnitVector(lookFrom - lookAt);
	u = UnitVector(cross(viewUp, w));
	v = cross(w, u);

	//lowerLeftCorner = Vector3f(-halfWidth, -halfHeight, -1.0);
	lowerLeftCorner = origin - halfWidth * focusDistance * u - halfHeight * focusDistance * v - focusDistance * w;
	horizontal = 2 * halfWidth * focusDistance * u;
	vertical = 2 * halfHeight * focusDistance * v;
}

Ray Camera::GetRay(float s, float t)
{
	Vector3f random = lensRadius *  RandomInUnitDisk();
	Vector3f offset = u * random.x() + v * random.y();
	return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
}

Vector3f Camera::RandomInUnitDisk()
{
	Vector3f point;
	do {
		point = 2.0 * Vector3f(MathUtils::GetRandom(), MathUtils::GetRandom(), 0) - Vector3f(1, 1, 0);
	} while (Scalar(point, point) >= 1.0);
	return point;
}
