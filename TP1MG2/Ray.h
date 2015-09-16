#pragma once
#include <Vector3.h>

// Classe représentant un Rayon (demi droite dans un espace 3D).
class Ray	
{
	Vector3 origin;
	Vector3 direction;
public:
	// Constructeurs.
	Ray();
	Ray(Vector3 origin_, Vector3 direction_) : origin(origin_), direction(direction_){};
	Ray(const Ray& r) : origin(r.origin), direction(r.direction){};
	
	// getters.
	Vector3 getOrigin()
	{
		return origin;
	}

	Vector3 getDirection()
	{
		return direction;
	}

};