#pragma once
#include "opunaire.h"
#include "Node.h"
#include <algorithm>

class Scale :
	public OpUnaire
{
private:
	double scale;
public:
	Scale(void) : OpUnaire() {}
	Scale(Node *p_, double scale_) : OpUnaire(p_), scale(scale_) {} // Pour depanner normalement pas Node et pas Primitives
	~Scale(void);

	bool inside(const Vector3 &p) const
	{
		return n->inside(((p - n->getOrigin()) / scale) + n->getOrigin());
	}

	double distance(const Vector3 &p) const
	{
		return n->distance((((p  - n->getOrigin())) / scale) + n->getOrigin()) * scale;

	}

	Vector3 normal(const Vector3 &p) const
	{
		return n->normal(((p - n->getOrigin()) / scale) + n->getOrigin());
	}

	Vector3 getColor(const Vector3 &p) const
	{
		return n->getColor(((p - n->getOrigin()) / scale) + n->getOrigin());
	}

	Vector3 getOrigin() const
	{
		return n->getOrigin();
	}

};

