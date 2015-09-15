#pragma once
#include <cmath>
// classe utilitaire représente les points dans l'espace 3D.
class Vector3 {
public:
	double x, y, z;

	// Contructeurs
	Vector3(double x_, double y_, double z_) :x(x_), y(y_), z(z_){};
	Vector3() :x(0.0), y(0.0), z(0.0){};
	Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z){};

	// Surcharge des operateurs arithmetiques.

	inline Vector3& operator=(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	inline Vector3& operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	inline Vector3& operator*(const double& x_) const
	{
		return Vector3(x * x_, y * x_, z * x_);
	}

	inline Vector3& operator/(const double& x_) const
	{
		return Vector3(x / x_, y / x_, z / x_);
	}

	inline bool operator!=(const Vector3& v) const
	{
		return v.x != x || v.y != y || v.x != x;
	}

	static inline Vector3& normalize(Vector3& v)
	{
		return v / v.normal();
	}

	inline double normal() const
	{
		return std::sqrt(x*x + y*y + z*z);
	}
	// pdt scalaire
	inline Vector3& operator*(const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
	// pdt vectoriel
	inline Vector3& operator^(const Vector3& v) const
	{
		double tmpX = x;
		double tmpY = y;

		int xRes = y*v.z - z*v.y;
		int yRes = z*v.x - tmpX * v.z;
		int zRes = tmpX * v.y - tmpY * v.x;

		return Vector3(xRes, yRes, zRes);
	}
	inline Vector3& operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	inline Vector3& inv()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}


};