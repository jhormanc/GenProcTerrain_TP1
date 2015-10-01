#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Constante.h"

class Cube
{
public:
	Vector3 o;
	double Largeur;

	Cube() {}
	Cube(Vector3 o_, float Largeur_) : o(o_), Largeur(Largeur_) {}

	inline Vector3 getO() const
	{
		return o;
	}

	inline double getLargeur() const
	{
		return Largeur;
	}

	bool inside(const Vector3 &p) const;

	inline Vector3 normal(Vector3 p) const
	{
		return Vector3::normalize(p - o);
	}

	double distance(const Vector3 & a) const;
};

