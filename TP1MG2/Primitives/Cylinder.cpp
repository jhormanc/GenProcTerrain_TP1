#include "Cylinder.h"


Vector3 Cylinder::getO() const
{
	return o;
}

bool Cylinder::inside(const Vector3 &p) const
{

	return false;
}

Vector3 Cylinder::normal(Vector3 p) const
{
	if (p.z > -h.y && p.z < h.y)
		return p - Vector3(0., 0., p.z);
	return Vector3(0.);
}

double Cylinder::distance(const Vector3 & p) const
{
	Vector2 d = Vector2(Vector2(p.x, p.z).normal(), p.y).abs() - h;
	return std::min(std::max(d.x, d.y), 0.0) + d.max(0.).normal();
}

Vector3 Cylinder::getColor(const Vector3 & p) const
{
	return Vector3(255.);
}
