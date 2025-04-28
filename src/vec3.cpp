#include "vec3.h"

Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
Vec3::Vec3(float x_) : x(x_), y(x_), z(x_) {}
Vec3::Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
Vec3::Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}


Vec3 Vec3::operator+() const {
	return *this;
}

Vec3 Vec3::operator-() const {
	return Vec3(-x, -y, -z);
}

Vec3& Vec3::operator+=(const Vec3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vec3& Vec3::operator-=(const Vec3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vec3& Vec3::operator*=(const Vec3& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

Vec3& Vec3::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vec3& Vec3::operator/=(const Vec3& rhs) {
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;

	return *this;
}

Vec3& Vec3::operator/=(float scalar) {
	if (scalar == 0.0f) {
		throw std::invalid_argument("divide by zero!");
	}

	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

float Vec3::Magnitude() const{
	return (float) sqrt(MagnitudeSquared());
}

float Vec3::MagnitudeSquared() const{
	return x * x + y * y + z * z;
}

void Vec3::Normalize(){
	float mag = Magnitude();
	
	if (mag > 0) {
		float invMag = 1.0f / mag;
		x *= invMag;
		y *= invMag;
		z *= invMag;
	}
}

Vec3 Vec3::GetUnitVec() const {
	Vec3 r(*this);
	r.Normalize();
	return r;
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator+(const Vec3& lhs, float scalar) {
	return lhs + Vec3(scalar, scalar, scalar);
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vec3 operator-(const Vec3& lhs, float scalar) {
	return lhs - Vec3(scalar, scalar, scalar);
}

Vec3 operator*(const Vec3& lhs, float scalar) {
	return Vec3(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar);
}

Vec3 operator*(float scalar, const Vec3& rhs) {
	return rhs * scalar;
}

Vec3 operator*(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

Vec3 operator/(const Vec3& lhs, float scalar) {
	if (scalar == 0) {
		throw std::invalid_argument("divide by zero!");
	}

	float invScalar = 1.0f / scalar;
	return lhs * invScalar;
}

bool operator==(const Vec3& lhs, const Vec3& rhs) {
	const float EPSILON = 1e-6f;

	return std::abs(lhs.x - rhs.x) < EPSILON &&
		std::abs(lhs.y - rhs.y) < EPSILON &&
		std::abs(lhs.z - rhs.z) < EPSILON;
}

bool operator!=(const Vec3& lhs, const Vec3& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Vec3& rhs) {
	os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
	return os;
}

float Dot(const Vec3& lhs, const Vec3& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vec3 Cross(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z ,
		lhs.x * rhs.y - lhs.y * rhs.x
	);
}

Vec3 Pow(const Vec3& lhs, float expo) {
	float x = pow(lhs.x, expo);
	float y = pow(lhs.y, expo);
	float z = pow(lhs.z, expo);

	return Vec3(x, y, z);
}

Vec3 Reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * Dot(n, v) * n;
}

bool Refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refract_ray) {
	Vec3 unit_v = v.GetUnitVec();
	float dt = Dot(unit_v, n);

	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);

	if (discriminant > 0) {
		refract_ray = ni_over_nt * (v - n * dt) - n * sqrt(discriminant);

		return true;
	}
	return false;
}

Vec3 Lerp(const Vec3& lhs, const Vec3 rhs, float t) {
	float x = Lerp(lhs.x, rhs.x, t);
	float y = Lerp(lhs.y, rhs.y, t);
	float z = Lerp(lhs.z, rhs.z, t);

	return Vec3(x, y, z);
}

Vec3 RandInUnitDisk() {
	Vec3 p;

	do {
		p = 2 * Vec3(Rand01(), Rand01(), 0) - Vec3(1, 1, 0);
	} while (Dot(p, p) >= 1);
	return p;
}

Vec3 RandUnitSphere() {
	Vec3 p;
	do {
		p = 2 * Vec3(Rand01(), Rand01(), Rand01()) - 1;
	} while (Dot(p, p) >= 1);

	return p;
}