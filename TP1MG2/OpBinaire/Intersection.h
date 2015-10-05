#pragma once
#include "opbinaire.h"
#include "../CSG/Primitive.h"
#include <algorithm>

class Intersection :
	public OpBinaire
{

public:
	Intersection(void) : OpBinaire() {}
	Intersection(Primitive *p1_, Primitive *p2_) : OpBinaire(p1_, p2_) {}
	~Intersection(void);

	bool inside(const Vector3 &p) const;

	double distance(const Vector3 &p) const;

	Vector3 normal(const Vector3 &p) const;

	Vector3 getColor(const Vector3 &p) const;

	Vector3 getOrigin() const;

};

