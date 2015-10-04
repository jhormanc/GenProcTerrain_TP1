#include "Torus.h"


Torus::~Torus(void)
{
}

bool Torus::inside(const Vector3 p) const
{
	double d = Circle::distance(p);

	return d < r;
}