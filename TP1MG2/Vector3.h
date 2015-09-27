#pragma once
#include <cmath>
// classe utilitaire represente les points dans l'espace 3D.
class Vector3 {
public:
	double x, y, z;

	// Contructeurs
	Vector3(double x_, double y_, double z_) :x(x_), y(y_), z(z_){};
	Vector3(double x_) :x(x_), y(x_), z(x_){};
	Vector3() :x(0.0), y(0.0), z(0.0){};
	Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z){};

	// Surcharge des operateurs arithmetiques.

	inline Vector3 operator=(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	inline Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline Vector3 operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	inline Vector3 operator*(const double& x_) const
	{
		return Vector3(x * x_, y * x_, z * x_);
	}

	inline Vector3 operator+(const double& x_) const
	{
		return Vector3(x + x_, y + x_, z + x_);
	}

	inline Vector3 operator/(const double& x_) const
	{
		return Vector3(x / x_, y / x_, z / x_);
	}

	inline bool operator!=(const Vector3& v) const
	{
		return v.x != x || v.y != y || v.x != x;
	}

	inline bool operator==(const Vector3& v) const
	{
		return v.x == x && v.y == y && v.z == z;
	}

	static inline Vector3 normalize(const Vector3& v)
	{
		double normalV = v.normal();
		return normalV == 0.0 ? Vector3(.0) : v / normalV; // Règle pb division 0
	}

	inline double normal() const
	{
		return std::sqrt(x*x + y*y + z*z);
	}

	// Produit scalaire
	inline double operator*(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	// Produit vectoriel
	inline Vector3 operator^(const Vector3& v) const
	{
		return Vector3(y*v.z - z*v.y,
						z*v.x - x * v.z,
						x * v.y - y * v.x);
	}
	inline Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	inline Vector3 inv()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	// Pour connaître la distance entre 2 points (vector3)
	static inline double distance(const Vector3& v1,const Vector3& v2)
	{
		return sqrt((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y)+(v1.z-v2.z)*(v1.z-v2.z));
	}

};