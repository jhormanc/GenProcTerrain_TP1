#include "Union.h"

Union::~Union(void)
{
}

bool Union::inside(const Vector3 &p) const 
{
	return n1->inside(p) || n2->inside(p);
}

double Union::distance(const Vector3 &p) const
{
	double d1 = n1->distance(p);
	double d2 = n2->distance(p);

	return std::min(d1, d2);
}

Vector3 Union::normal(const Vector3 &p) const
{
	double d1 = n1->distance(p);
	double d2 = n2->distance(p);

	if (d1 < d2)
		return n1->normal(p);

	return n2->normal(p);
}

Vector3 Union::getColor(const Vector3 &p) const
{ 
	double d1 = n1->distance(p);
	double d2 = n2->distance(p);

	if (d1 < d2)
		return n1->getColor(p);

	return n2->getColor(p);
}

Vector3 Union::getOrigin() const
{
	return (n1->getOrigin() + n2->getOrigin() )/ 2.;
}