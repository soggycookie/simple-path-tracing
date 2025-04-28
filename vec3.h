#pragma once

#include <cmath>
#include <ostream>
#include "stdexcept"
#include "math-common.h"

class Vec3 {
	public:
		union {
			struct { float x, y, z; };
			struct { float r, g, b; };
		};

		Vec3();
		Vec3(float x_);
		
		Vec3(float x_, float y_, float z_);
		Vec3(const Vec3& v);

		Vec3 operator-() const;
		Vec3 operator+() const;

		Vec3& operator+=(const Vec3& rhs);
		Vec3& operator-=(const Vec3& rhs);
		Vec3& operator*=(const Vec3& rhs);
		Vec3& operator*=(float scalar);
		Vec3& operator/=(const Vec3& rhs);
		Vec3& operator/=(float scalar);

		float Magnitude() const;
		float MagnitudeSquared() const;
		void Normalize();
		Vec3 GetUnitVec() const;

};

Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
Vec3 operator+(const Vec3& lhs, float scalar);
Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
Vec3 operator-(const Vec3& lhs, float scalar);
Vec3 operator*(const Vec3& lhs, float scalar);
Vec3 operator*(const Vec3& lhs, const Vec3& rhs);
Vec3 operator*(float scalar, const Vec3& rhs);
Vec3 operator/(const Vec3& lhs, float scalar);


bool operator==(const Vec3& lhs, const Vec3& rhs);
bool operator!=(const Vec3& lhs, const Vec3& rhs);

std::ostream& operator<<(std::ostream& os, const Vec3& rhs);

float Dot(const Vec3& lhs, const Vec3& rhs);
Vec3 Cross(const Vec3& lhs, const Vec3& rhs);

Vec3 Reflect(const Vec3& v, const Vec3& n);
bool Refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refract_ray);

Vec3 Pow(const Vec3& lhs, float expo);

Vec3 RandUnitSphere();
Vec3 RandInUnitDisk();

Vec3 Lerp(const Vec3& lhs, const Vec3 rhs, float t);