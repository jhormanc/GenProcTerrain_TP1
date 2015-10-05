#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Constante.h"

class Sphere
{

public:
	Vector3 o;
	double rayon;
	Vector3 color;

	Sphere() {}
	Sphere(Vector3 o_, float rayon_, Vector3 color_) : o(o_), rayon(rayon_), color(color_) {}

	inline Vector3 getO() const
	{
		return o;
	}

	inline double getRayon() const
	{
		return rayon;
	}

	inline Vector3 getColor(const Vector3 & p) const
	{
		return color;
	}

	inline bool inside(const Vector3 &p) const
	{
		//return (p - o).normal() <= rayon;
		return Vector3::distance(o, p) <= rayon;
	}

	inline Vector3 normal(Vector3 p) const
	{
		return Vector3::normalize(p - o);
	}

	double distance(const Vector3 & a) const;
};