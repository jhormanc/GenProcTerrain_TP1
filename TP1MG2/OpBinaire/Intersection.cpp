#include "Intersection.h"

Intersection::~Intersection()
{
}

bool Intersection::inside(const Vector3 &p) const
{
	return n1->inside(p) && n2->inside(p);
}

double Intersection::distance(const Vector3 &p) const
{
	double d1 = n1->distance(p);
	double d2 = n2->distance(p);

	return std::max(d1, d2);
}

Vector3 Intersection::normal(const Vector3 &p) const
{
	if (inside(p))
		return n1->normal(p);

	return n2->normal(p);
}

Vector3 Intersection::getColor(const Vector3 &p) const
{
	if (inside(p))
		return n1->getColor(p);

	return n2->getColor(p);
}

Vector3 Intersection::getOrigin() const
{
	return (n1->getOrigin() + n2->getOrigin()) / 2.;
}