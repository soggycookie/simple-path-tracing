#include "ray.h"

Ray::Ray() : ro(Vec3(0,0,0)), rd(Vec3(0,0,0)) {}
Ray::Ray(const Vec3& ro_, const Vec3& rd_) : ro(ro_), rd(rd_){}

Vec3 Ray::PointAlongTheRay(float t) const {
	return ro + rd * t;
}