#include "Box.h"


Vector3 Box::getO() const
{
	return o;
}

bool Box::inside(const Vector3 &p) const
{

	return (p.x > o.x - b.x && p.x < o.x + b.x) &&
		(p.y > o.y - b.y && p.y < o.y + b.y) &&
		(p.z > o.z - b.z && p.z < o.z + b.z);
}

Vector3 Box::normal(Vector3 p) const
{
	Vector3 bOn2 = b;
	if (p.x > o.x - bOn2.x && p.x < o.x + bOn2.x)
	{
		return Vector3::normalize(o - Vector3(bOn2.x, 0., 0.));
	}
	else if (p.y > o.y - bOn2.y && p.y < o.y + bOn2.y)
	{
		return Vector3::normalize(o - Vector3(0., bOn2.y, 0.));
	}
	else if (p.z > o.z - bOn2.z && p.z < o.z + bOn2.z)
	{
		return Vector3::normalize(o - Vector3(0., 0., bOn2.z));
	}
	return Vector3::normalize(o - p); // arretes et coin
}

double Box::distance(const Vector3 & p) const
{
	Vector3 d = (p - o).abs() - b;
	return std::min(std::max(d.x, std::max(d.y, d.z)), 0.0) + d.max(0.0).normal();
}

Vector3 Box::getColor(const Vector3 & p) const
{
	return Vector3(255.);
}
