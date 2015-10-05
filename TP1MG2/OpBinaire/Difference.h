#pragma once
#include "OpBinaire\OpBinaire.h"
#include "CSG\Primitive.h"
#include <algorithm>

class Difference :
	public OpBinaire
{

public:
	Difference(void) : OpBinaire() {}
	Difference(Primitive *p1_, Primitive *p2_) : OpBinaire(p1_, p2_) {}
	~Difference(void);

	bool inside(const Vector3 &p) const
	{
		return n1->inside(p) && !n2->inside(p);
	}

	double distance(const Vector3 &p) const
	{
		double d1 = n1->distance(p);
		double d2 = n2->distance(p);

		return std::max(-d1, d2);
	}

	Vector3 normal(const Vector3 &p) const
	{
		if (inside(p))
			return n1->normal(p).inv();

		return n2->normal(p);
	}

	Vector3 getColor(const Vector3 &p) const
	{
		if (inside(p))
			return n1->getColor(p);
		return n2->getColor(p);
	}

	Vector3 getOrigin() const
	{
		return (n1->getOrigin() + n2->getOrigin()) / 2.;
	}
};

