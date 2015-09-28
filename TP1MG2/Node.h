#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Constante.h"

class Node
{
public:
	Node() {}
	~Node();

	virtual bool inside(const Vector3 &p) const = 0;

	bool intersect(Ray & r, double & dist) const;

	virtual double distance(const Vector3 & a) const = 0;

	virtual Vector3 getColor(const Vector3 & p) const = 0;

};