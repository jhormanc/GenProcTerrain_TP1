#pragma once
#include "Vector3.h"
#include "Ray.h"

class Sphere {
	Vector3 o;
	double rayon;


public:
	Sphere(Vector3 o_, float rayon_) :o(o_), rayon(rayon_){};
	inline Vector3 getO() const
	{
		return o;
	}

	inline double getRayon() const
	{
		return rayon;
	}

	inline bool isIn(Vector3 p) const
	{
		return (p - o).normal() <= rayon;
	}

	Vector3 intersection(Ray r) const
	{
		Vector3 p = r.getOrigin();
		double eps = .5;
		for (int i = 0; i < 200; i++)
		{
			if (isIn(p))
			{
				return p;
			}
			p += r.getDirection() * eps;
		}
		return Vector3(-10, -10, -10);
	}
};