#include <iostream>
#include <fstream>
#include "hitable.h"
#include "camera.h"
#include "material.h"
#include <stdlib.h>
#include <time.h>

Vec3 GetColor(const Ray& r, Hitable* world, int depth) {
	HitRecord rec;
	if (world->Hit(r, 0.001f, FLT_MAX, rec)) {
		Ray scattered;
		Vec3 attenuation;

		if (depth < 50 && rec.mat_ptr->Scatter(r, rec, attenuation, scattered)) {
			return attenuation * GetColor(scattered, world, depth + 1);
		}
		else {
			return Vec3(0, 0, 0);
		}
	}

	Vec3 unitRd = r.rd.GetUnitVec();
	Vec3 bottomColor = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 topColor = Vec3(0.5f, 0.7f, 1.0f);
	//Vec3 topColor = Vec3(1.0f, 0.7f, 0.0f);
	float t = unitRd.y * 0.5f + 0.5f;
	return Lerp(bottomColor, topColor, t);
}


int main() {
	srand((unsigned int)time(NULL));  // seed the random number generator

	int nx = 1200;
	int ny = 600;
	int ns = 150;
	bool antiAlias = true;
	bool dof = false;

	const int n = 21;
	Hitable* list[n];
	list[0] = new Sphere(Vec3(0, -1000.5f, -1), 1000, new Lambertian(Vec3(0.8f, 0.8f, 0.8f)));
	list[1] = new Sphere(Vec3(0, 0, -6), 0.5f, new Lambertian(Vec3(0.8f, 0.2f, 0.5f)));
	list[2] = new Sphere(Vec3(2, 0, -6), 0.5f, new Lambertian(Vec3(1, 0.2f, 0.5f)));
	list[3] = new Sphere(Vec3(2, 0, -5), 0.5f, new Lambertian(Vec3(0.3f, 1, 0.6f)));
	list[4] = new Sphere(Vec3(0, 0, -3), 0.5f, new Metal(Vec3(0.2f, 0.1f, 0.9f), 0));
	list[5] = new Sphere(Vec3(1, 0, -4), 0.5f, new Dielectric(Vec3(1), 1.5f));
	list[6] = new Sphere(Vec3(1, 0, -4), -0.45f, new Dielectric(Vec3(1), 1.5f));
	list[7] = new Sphere(Vec3(6, 1, -8), 1.5f, new Dielectric(Vec3(1, 0, 0), 1.2f));
	list[8] = new Sphere(Vec3(-4, 1, -8), 1.5f, new Metal(Vec3(0, 1, 0), 0.5f));
	list[9] = new Sphere(Vec3(-4, 0, -3), 0.5f, new Metal(Vec3(0, 0.2f, 1), 0.2f));
	list[10] = new Sphere(Vec3(-2, 0, -4), 0.5f, new Lambertian(Vec3(0, 0.8f, 1)));
	list[11] = new Sphere(Vec3(-8, 0, -6), 0.5f, new Lambertian(Vec3(0, 1, 0.2f)));
	list[12] = new Sphere(Vec3(-5, 0, -6), 0.5f, new Metal(Vec3(0.5f, 0, 0.8f), 0));
	list[13] = new Sphere(Vec3(-7, 0, -3), 0.5f, new Metal(Vec3(0.0f, 0.4f, 0.8f), 1));
	list[14] = new Sphere(Vec3(-2, 0, -4), 0.5f, new Metal(Vec3(0.2f, 0.2f, 0.2f), 0));
	list[15] = new Sphere(Vec3(-3, 0, -6), 0.5f, new Metal(Vec3(0.0f, 0.2f, 0.7f), 0));
	list[16] = new Sphere(Vec3(5, 0, -5), 0.5f, new Metal(Vec3(1, 1, 1), 0));
	list[17] = new Sphere(Vec3(-2, 0, -1), 0.5f, new Dielectric(Vec3(1, 1, 1), 1.3f));
	list[18] = new Sphere(Vec3(-2, 0, -1), -0.45f, new Dielectric(Vec3(1, 1, 1), 1.3f));
	list[19] = new Sphere(Vec3(3, 0, -2), 0.5f, new Metal(Vec3(0, 1, 1), 0));
	list[20] = new Sphere(Vec3(0, 0, -1), 0.5f, new Metal(Vec3(0.9f, 0.5f, 0), 0));

	Hitable* world = new HitableList(list, n);

	std::ofstream outputFile("output.ppm");
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";

	Vec3 look_from(0, 3, -1);
	Vec3 look_at(0, 0, -3);
	float focus_dist = (look_from - look_at).Magnitude();
	float aperture = 2;
	float vfov = 90;

	if (!dof) {
		aperture = 0;
		focus_dist = 1;
	}

	Camera cam(look_from, look_at, Vec3(0, 1, 0), vfov, float(nx) / float(ny), aperture, focus_dist);


	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++)
		{
			Vec3 col;

			if (antiAlias) {
				for (int s = 0; s < ns; s++) {
					float u = float(i + Rand01()) / float(nx);
					float v = float(j + Rand01()) / float(ny);
					Ray r = cam.GetRay(u, v);
					col += GetColor(r, world, 0);
				}
				col /= float(ns);
			}
			else {
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);

				Ray r = cam.GetRay(u, v);
				col = GetColor(r, world, 0);
			}


			//gamma-corrected
			col = Pow(col, 1.0f / 2.4f);
			
			col *= 255.99f;

			outputFile << int(col.r) << " " << int(col.g) << " " << int(col.b) << "\n";
		}
	}
	outputFile << std::endl;

	for (int i = 0; i < 4; i++) {
		Hitable* h = list[i];
		Sphere* s = dynamic_cast<Sphere*>(h);

		delete s;
		delete h;
	}

	delete world;
}



