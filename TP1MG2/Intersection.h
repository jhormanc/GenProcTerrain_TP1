#pragma once
#include "opbinaire.h"
#include "Primitive.h"
#include <algorithm>

class Intersection :
	public OpBinaire
{

public:
	Intersection(void) : OpBinaire() {}
	Intersection(Primitive *p1_, Primitive *p2_) : OpBinaire(p1_, p2_) {}
	~Intersection(void);

	bool inside(const Vector3 &p) const
	{
		return n1->inside(p) && n2->inside(p);
	}

	double distance(const Vector3 &p) const
	{
		double d1 = n1->distance(p);
		double d2 = n2->distance(p);

		return std::max(d1, d2);
	}

	Vector3 normal(const Vector3 &p) const
	{
		double d1 = n1->distance(p);
		double d2 = n2->distance(p);

		if (d1 > d2)
			return n1->normal(p);

		return n2->normal(p);
	}

	Vector3 getColor(const Vector3 &p) const
	{
		double d1 = n1->distance(p);
		double d2 = n2->distance(p);

		if (d1 > d2)
			return n1->getColor(p);

		return n2->getColor(p);
	}


};

