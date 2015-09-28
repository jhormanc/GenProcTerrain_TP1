#pragma once
#include "primitive.h"
#include "Sphere.h"

class CSG_Sphere :
	public Primitive, public Sphere
{
public:
	CSG_Sphere(void) : Primitive(), Sphere() {}

	CSG_Sphere(Vector3 o_, float rayon_) : Primitive(), Sphere(o_, rayon_) {}

	~CSG_Sphere(void);
	
	bool inside(const Vector3 &p) const 
	{ 
		return inside_s(p);
	} 

	double distance(const Vector3 & a) const
	{
		return distance_s(a);
	}

	Vector3 getColor(const Vector3 &p) const { return Vector3(255.); }

protected:



};

