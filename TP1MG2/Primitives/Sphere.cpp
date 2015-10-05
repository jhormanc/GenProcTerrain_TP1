#pragma once
#include "Sphere.h"


double Sphere::distance(const Vector3 & a) const
{
	/*
	if (Vector3::distance(a, o) > rayon){
		return Vector3::distance(a, o) - rayon;
	}
	else{
		return 0.;
	} */
	return (a - o).normal() - rayon;

}