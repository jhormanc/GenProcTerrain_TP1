#pragma once
#include "Vector3.h"
// classe utilitaire represente les points dans l'espace 3D.
class Mat3x3 {
public:
	Vector3 line1;
	Vector3 line2;
	Vector3 line3;

	// Contructeurs
	Mat3x3() :line1(Vector3(0.)), line2(Vector3(0.)), line3(Vector3(0.)){};
	Mat3x3(Vector3 line1_, Vector3 line2_, Vector3 line3_) :line1(line1_), line2(line2_), line3(line3_){};
	// Surcharge des operateurs arithmetiques.

	inline Vector3 operator*(const Vector3& v) const
	{
		
		return Vector3(v.x * line1.x + v.y * line1.y + v.z * line1.z,
						v.x * line2.x + v.y * line2.y + v.z * line2.z,
						v.x * line3.x + v.y * line3.y + v.z * line3.z);
	}

	

};