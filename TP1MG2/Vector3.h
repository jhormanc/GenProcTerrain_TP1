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

	static Vector3& normalize(Vector3& v);
	double normal() const;
	// Surcharge des operateurs arithmetiques.
	Vector3& operator=(const Vector3& v);
	Vector3& operator+(const Vector3& v);
	Vector3& operator/(const double x_);
	// pdt scalaire
	Vector3& operator*(const Vector3& v);
	// pdt vectoriel
	Vector3& operator^(const Vector3& v);
	Vector3& operator*(const double x_);

	//Vector3& operator+(int n);
	Vector3& operator-(const Vector3& v);
	Vector3& inv();
};