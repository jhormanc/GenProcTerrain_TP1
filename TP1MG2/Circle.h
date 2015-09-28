#pragma once
#include "Vector3.h"

class Circle
{
protected:
	Vector3 centre;
	Vector3 normal;
	double rayon;

public:
	Circle(void) : centre(Vector3(0.)), normal(Vector3(1.)), rayon(1.) {}
	Circle(const Vector3 centre_, const Vector3 normal_, const double rayon_) : centre(centre_), normal(Vector3::normalize(normal_)), rayon(rayon_) {}
	~Circle(void);

	double distance(const Vector3 p) const;
};

