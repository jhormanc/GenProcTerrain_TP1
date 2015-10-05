#include "Difference.h"

Difference::~Difference()
{
}

bool Difference::inside(const Vector3 &p) const
{
	return n1->inside(p) && !n2->inside(p);
}

// Not working (on a besoin de la distance à l'intérieur de la primitive)
double Difference::distance(const Vector3 &p) const
{
	double d1 = n1->distance(p);
	double d2 = n2->distance(p);

	return std::max(d1, -d2);
}

Vector3 Difference::normal(const Vector3 &p) const
{
	if (n2->inside(p))
		return n2->normal(p).inv();

	return n1->normal(p);
}

Vector3 Difference::getColor(const Vector3 &p) const
{
	/*if (n2->inside(p))
		return n2->getColor(p); */
	return n1->getColor(p);
}

Vector3 Difference::getOrigin() const
{
	return (n1->getOrigin());
}