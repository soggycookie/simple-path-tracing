#pragma once

#include "vec3.h"

class Ray {
public:
	Vec3 ro, rd;

	Ray();
	Ray(const Vec3& ro_, const Vec3& rd_);

	Vec3 PointAlongTheRay(float t) const;
};