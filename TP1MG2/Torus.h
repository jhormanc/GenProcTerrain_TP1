#pragma once
#include "circle.h"
class Torus :
	public Circle
{
protected:
	double r;

public:
	Torus(void) : Circle(), r(0.1) {}
	Torus(const double r_, const Vector3 centre_circle, const Vector3 normal_circle, const double rayon_circle) : Circle(centre_circle, normal_circle, rayon_circle), r(r_) {}
	~Torus(void);

	bool inside(const Vector3 p) const;

};

