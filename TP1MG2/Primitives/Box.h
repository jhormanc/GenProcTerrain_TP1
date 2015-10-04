#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Constante.h"
#include <algorithm>

class Box
{
public:
	Vector3 o;
	Vector3 b;

	Box() {}
	Box(Vector3 o_, Vector3 b_) : o(o_), b(b_) {}

	Vector3 getO() const;

	bool inside(const Vector3 &p) const;

	Vector3 normal(Vector3 p) const;

	double distance(const Vector3 & p) const;

	Vector3 getColor(const Vector3 & p) const;
};

