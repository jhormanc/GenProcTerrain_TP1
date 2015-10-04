#pragma once
#include "primitive.h"
#include "../Primitives/Cube.h"

class CSG_Cube : 
	public Primitive, public Cube
{
public:
	CSG_Cube(void): Primitive(), Cube() {}
	
	CSG_Cube(Vector3 o_ , float Largeur_) : Primitive(), Cube(o_,Largeur_){}
	
	~CSG_Cube(void);

bool inside(const Vector3 &p) const {

		return Cube::inside(p);
	} 
	
	double distance(const Vector3 & a) const{

		return Cube::distance(a);
	}
	 
	Vector3 getColor(const Vector3 &p) const { return Vector3(255.); }

	virtual Vector3 getOrigin() const
	{
		return getO();
	}

	Vector3 normal(const Vector3& p )const{
		return Cube::normal(p);
	};



protected:

};

