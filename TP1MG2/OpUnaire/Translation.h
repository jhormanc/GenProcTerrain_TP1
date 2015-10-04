#pragma once
#include "opunaire.h"
#include "Node.h"
#include <algorithm>

class Translation :
	public OpUnaire
{
private:
	Vector3 t;
public:
	Translation(void) : OpUnaire() {}
	Translation(Node *p_, Vector3 t_) : OpUnaire(p_), t(t_) {} // Pour depanner normalement pas Node et pas Primitives
	~Translation(void);

	bool inside(const Vector3 &p) const
	{
		return n->inside(p - t);
	}

	double distance(const Vector3 &p) const
	{
		return n->distance(p - t);

	}

	Vector3 normal(const Vector3 &p) const
	{
		return n->normal(p - t);
	}

	Vector3 getColor(const Vector3 &p) const
	{
		return n->getColor(p - t);
	}

	Vector3 getOrigin() const
	{
		return n->getOrigin() + t;
	}
};

