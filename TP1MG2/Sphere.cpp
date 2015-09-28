#pragma once
#include "Sphere.h"


double Sphere::distance_s(const Vector3 & a) const
{

	if (Vector3::distance(a, o) > rayon){
		return Vector3::distance(a, o) - rayon;
	}
	else{
		return 0.;
	}
}