#pragma once
#include "Vector3.h"
#include "Ray.h"

class Node
{
public:
	Node() {}
	~Node();

	virtual bool inside(const Vector3 &p) const = 0;

	bool intersect(const Ray r, double t) const;

	virtual Vector3 getColor(const Vector3 &p) const = 0;

};