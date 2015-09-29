#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Constante.h"

class Sphere
{

public:
	Vector3 o;
	double rayon;

	Sphere() {}
	Sphere(Vector3 o_, float rayon_) : o(o_), rayon(rayon_) {}

	inline Vector3 getO() const
	{
		return o;
	}

	inline double getRayon() const
	{
		return rayon;
	}

	inline bool inside(const Vector3 &p) const
	{
		return (p - o).normal() <= rayon;
	}

	inline Vector3 normal(Vector3 p) const
	{
		return Vector3::normalize(p - o);
	}

	double distance(const Vector3 & a) const;
};