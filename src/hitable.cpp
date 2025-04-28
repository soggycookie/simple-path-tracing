#include "hitable.h"

Sphere::Sphere(): center(Vec3(0, 0, 0)), radius(0), sphere_mat_ptr(nullptr){}
Sphere::Sphere(Vec3 center_, float radius_, Material* sphere_mat_ptr_): 
	center(center_), radius(radius_), sphere_mat_ptr(sphere_mat_ptr_){}

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
	Vec3 oc = r.ro - center;
	float a = Dot(r.rd, r.rd);
	float b = 2 * Dot(oc, r.rd);
	float c = Dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant >= 0) {
		float t_near = (-b - sqrt(discriminant)) / (2 * a);

		if (t_near > t_min && t_near < t_max) {
			rec.t = t_near;
			rec.p = r.PointAlongTheRay(t_near);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = sphere_mat_ptr;
			return true;
		}
	}
	return false;
}

HitableList::HitableList(): list(NULL), list_size(0){}
HitableList::HitableList(Hitable** l_, int n_): list(l_), list_size(n_){}

bool HitableList::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
	HitRecord temp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->Hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}


