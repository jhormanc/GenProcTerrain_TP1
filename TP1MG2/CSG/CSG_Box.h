#pragma once
#include "primitive.h"
#include "../Primitives/Box.h"

class CSG_Box :
	public Primitive, public Box
{
public:
	CSG_Box(void) : Primitive(), Box() {}

	CSG_Box(Vector3 o_, Vector3 p_) : Primitive(), Box(o_, p_) {}

	~CSG_Box(void);

	bool inside(const Vector3 &p) const
	{
		return Box::inside(p);
	}

	double distance(const Vector3 & a) const
	{
		return Box::distance(a);
	}

	inline Vector3 getColor(const Vector3 & p) const
	{
		return Box::getColor(p);
	}

	Vector3 normal(const Vector3& p)const{
		return Box::normal(p);
	};

	Vector3 getOrigin() const
	{
		return Box::getO();
	}
};

