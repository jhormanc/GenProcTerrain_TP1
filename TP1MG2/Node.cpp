#include "Node.h"

bool Node::intersect(Ray & r, double & dist) const
{
	dist = 0.;
	Vector3 res;
	for (int i = 0; i < 256; i++)
	{
		res = r.getOrigin() + (r.getDirection() * dist);
		double h = distance(res);
		// res.z - tmp.z;
		if (h < (0.01)) return true;
		dist += h;
	}
	dist = Constante::noIntersect;
	return false;
}

Node::~Node(void)
{
}