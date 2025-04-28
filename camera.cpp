#include "camera.h"
#define PI 3.1415

Camera::Camera(Vec3 look_from, Vec3 look_at, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
	lens_radius = aperture / 2;
	
	float theta = vfov * PI / 180.0f;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	
	origin = look_from;
	
	w = (look_from - look_at).GetUnitVec();
	u = (Cross(vup, w)).GetUnitVec();
	v = Cross(w, u);

	lower_left_corner = origin - half_width * focus_dist  * u - half_height * focus_dist  * v - focus_dist * w;
	horizontal = 2 * half_width * focus_dist * u;
	vertical = 2 * half_height * focus_dist * v;

}

Ray Camera::GetRay(float s, float t) const {
	Vec3 rd = lens_radius * RandInUnitDisk();
	Vec3 offset = u * rd.x + v * rd.y;
	return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}