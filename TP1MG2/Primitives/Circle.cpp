#include "Circle.h"

Circle::~Circle(void)
{
}

double Circle::distance(const Vector3 p) const
{
	double h = (p - centre) * normal;
	double l = std::sqrt((centre - p) * (centre - p) - h * h);

	return std::sqrt(h * h + (l - rayon) * (l - rayon));
}