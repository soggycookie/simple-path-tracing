#include "material.h"
#include "math-common.h"

Lambertian::Lambertian(const Vec3& albedo_) {
	albedo = albedo_;
}

bool Lambertian::Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	Vec3 target = rec.p + rec.normal + RandUnitSphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = albedo;
	
	return true;
}

Metal::Metal(const Vec3& albedo_, float fuzz_) {
	albedo = albedo_;

	if (fuzz < 1)
		fuzz = fuzz_;
	else {
		fuzz = 1;
	}
}

bool Metal::Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	Vec3 reflect_ray = Reflect(r_in.rd.GetUnitVec(), rec.normal);
	scattered = Ray(rec.p, reflect_ray + fuzz * RandUnitSphere());
	attenuation = albedo;
	
	return Dot(scattered.rd.GetUnitVec(), rec.normal) > 0;
}

Dielectric::Dielectric( Vec3 albedo_, float ref_idx_): albedo(albedo_), ref_idx(ref_idx_){}

bool Dielectric::Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	Vec3 outward_normal;
	Vec3 reflect_ray = Reflect(r_in.rd, rec.normal);
	float ni_over_nt;
	float cosine;
	Vec3 refract_ray;
	float reflect_prob;

	attenuation = albedo;
	
	if (Dot(r_in.rd, rec.normal) > 0) {
		outward_normal = -rec.normal;
		ni_over_nt = ref_idx;
		cosine = ref_idx * Dot(r_in.rd, rec.normal) / r_in.rd.Magnitude();
	}
	else {
		outward_normal = rec.normal;
		ni_over_nt = 1.0f / ref_idx;
		cosine = -Dot(r_in.rd, rec.normal) / r_in.rd.Magnitude();
	}



	if (Refract(r_in.rd, outward_normal, ni_over_nt, refract_ray)) {
		reflect_prob = Schlick(cosine, ref_idx);
	}
	else{
		reflect_prob = 1.0f;
	}

	if (Rand01() < reflect_prob) {
		scattered = Ray(rec.p, reflect_ray);
	}
	else {
		scattered = Ray(rec.p, refract_ray);
	}

	return true;
}
