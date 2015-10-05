#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Constante.h"
#include <algorithm>
//#include <amp.h>


class Triangle
{
public:
	Vector3 a;
	Vector3 b;
	Vector3 c;

	Triangle() {}
	Triangle(Vector3 a_, Vector3 b_, Vector3 c_) : a(a_), b(b_) , c(c_) {}

	Vector3 getO() const;

	bool inside(const Vector3 &p) const;

	Vector3 normal(Vector3 p) const;

	double sign(double)const;

	double clamping(double,double,double) const;

	double distance(const Vector3 & p) const;

	Vector3 getColor(const Vector3 & p) const;
};

