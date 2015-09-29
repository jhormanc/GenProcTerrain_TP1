#include "Node.h"

bool Node::intersect(Ray & r, double & dist) const
{
	dist = 0.;
	Vector3 res;
	for (int i = 0; i < 500; i++)
	{
		res = r.getOrigin() + (r.getDirection() * dist);
		double h = distance(res);
		if (h > Constante::noIntersect) // Car pour le terrain on calcule la distance en z seulement (donc noneVect possible) en attendant la box
		{
			if (h < (0.01)) return true;
			dist += h;
		}
		else
		{
			dist += 1.;
		}
	}
	dist = Constante::noIntersect;
	return false;
}

Node::~Node(void)
{
}