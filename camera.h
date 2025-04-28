#pragma once
#include "ray.h"

class Camera {
public:
	Vec3 origin;
	Vec3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 u, v, w;
	float lens_radius;

	Camera(Vec3 look_from, Vec3 look_at, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist);

	Ray GetRay(float s, float t) const;
};