#pragma once
#include "primitive.h"
#include "../Primitives/Cylinder.h"

class CSG_Cylinder :
	public Primitive, public Cylinder
{
public:
	CSG_Cylinder(void) : Primitive(), Cylinder() {}

	CSG_Cylinder(Vector3 o_, Vector2 p_) : Primitive(), Cylinder(o_, p_) {}

	~CSG_Cylinder(void);

	bool inside(const Vector3 &p) const
	{
		return Cylinder::inside(p);
	}

	double distance(const Vector3 & a) const
	{
		return Cylinder::distance(a);
	}

	inline Vector3 getColor(const Vector3 & p) const
	{
		return Cylinder::getColor(p);
	}

	Vector3 normal(const Vector3& p)const{
		return Cylinder::normal(p);
	};

	Vector3 getOrigin() const
	{
		return Cylinder::getO();
	}
};

