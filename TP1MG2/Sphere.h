#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Constante.h"
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

	inline Vector3 normal(Vector3 p) const
	{
		return Vector3::normalize(p - o);
	}

	bool intersection(Ray r, double& t) const
	{
		
		Vector3 op = o - r.getOrigin();		// Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
		double b = r.getDirection() * op;
		t = 0.0;
		double det = b * b - (op * op) + rayon * rayon;
		if (det < 0)
			return (t = Constante::noIntersect);
		else
			det = std::sqrt(det);
		return (t = b - det) >= 0 ? t : ((t = b + det) >= 0 ? t : Constante::noIntersect);
	}
};