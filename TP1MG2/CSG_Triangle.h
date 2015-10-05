#pragma once
#include "../CSG/primitive.h"
#include "triangle.h"

class CSG_Triangle :
	public Primitive, public Triangle
{
public:
	CSG_Triangle(void) : Primitive(), Triangle() {}

	CSG_Triangle(Vector3 a_, Vector3 b_, Vector3 c_) : Primitive(), Triangle(a_, b_,  c_) {}

	~CSG_Triangle(void);

	bool inside(const Vector3 &p) const
	{
		return Triangle::inside(p);
	}

	double distance(const Vector3 & a) const
	{
		return Triangle::distance(a);
	}

	inline Vector3 getColor(const Vector3 & p) const
	{
		return Triangle::getColor(p);
	}

	Vector3 normal(const Vector3& p)const{
		return Triangle::normal(p);
	};

	Vector3 getOrigin() const
	{
		return Triangle::getO();
	}
};
