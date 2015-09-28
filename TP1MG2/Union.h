#pragma once
#include "opbinaire.h"
#include "Primitive.h"

class Union :
	public OpBinaire
{

public:
	Union(void) : OpBinaire() {}
	Union(Primitive *p1_, Primitive *p2_) : OpBinaire(p1_, p2_) {}
	~Union(void);

	bool inside(const Vector3 &p) const 
	{
		return n1->inside(p) && n2->inside(p);
	}

	Vector3 getColor(Vector3 p) const { return Vector3(0.); }


};

