#pragma once
#include "ray.h"

class Material;

struct HitRecord {
	float t;
	Vec3 p;
	Vec3 normal;
	Material* mat_ptr;
};

class Hitable {
public:
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

class Sphere : public Hitable {
public:
	Vec3 center;
	float radius;
	Material* sphere_mat_ptr;

	Sphere();
	Sphere(Vec3 center_, float radius_, Material* sphere_mat_ptr_);
	
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
};

class HitableList : public Hitable {
public:
	Hitable** list;
	int list_size;

	HitableList();
	HitableList(Hitable** l_, int n_);

	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
};