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

	bool inside(const Vector3 &p) const;

	// Not working (on a besoin de la distance à l'intérieur de la primitive)
	double distance(const Vector3 &p) const;

	Vector3 normal(const Vector3 &p) const;

	Vector3 getColor(const Vector3 &p) const;

	Vector3 getOrigin() const;
};

