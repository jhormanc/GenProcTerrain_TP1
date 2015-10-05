#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include <algorithm>

class Cylinder
{
public:
	Vector3 o;
	Vector2 h;

	Cylinder() {}
	Cylinder(Vector3 o_, Vector2 h_) : o(o_), h(h_) {}

	Vector3 getO() const;

	bool inside(const Vector3 &p) const;

	Vector3 normal(Vector3 p) const;

	double distance(const Vector3 & p) const;

	Vector3 getColor(const Vector3 & p) const;
};

