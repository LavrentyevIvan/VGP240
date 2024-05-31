#pragma once

struct Vector3
{
	float x, y,z;

	constexpr Vector3() :x(0.0f), y(0.0f), z(0.0f) {}

	constexpr Vector3(float _s) : x(_s), y(_s), z(_s) {}
	constexpr Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}

	Vector3 operator+(const Vector3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z}; }

	Vector3 operator-(const Vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }

	Vector3 operator/(float s) const { return { x / s, y / s, z /s }; }

	Vector3 operator*(float s) const { return { x * s, y * s, z *s }; }

	Vector3 operator-() const { return { -x, -y, -z  }; }


	Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
	Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }
};