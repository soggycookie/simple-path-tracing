#pragma once
#include "hitable.h"


class Material {
public:
	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
	Vec3 albedo;
	
	Lambertian(const Vec3& albedo_);

	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
};

class Metal : public Material {
public:
	Vec3 albedo;
	float fuzz;

	Metal(const Vec3& albedo_, float fuzz_);

	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
};

class Dielectric : public Material {
public:
	Vec3 albedo;
	float ref_idx;

	Dielectric( Vec3 albedo_, float ref_idx_);

	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;

};