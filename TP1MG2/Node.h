#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Constante.h"

class Node
{
public:
	Node() {}
	~Node();

	virtual bool inside(const Vector3 &p) const = 0;

	bool intersect(Ray & r, double & dist) const;

	virtual double distance(const Vector3 & a) const = 0;

	virtual Vector3 getColor(const Vector3 & p) const = 0;

	virtual Vector3 normal(const Vector3 & ) const = 0;

	virtual Vector3 getOrigin() const = 0; // Car pour les transformations locales (scale, rotation) on est oblige de mettre l'objet a l'origine, d'effectuer loperation et de le remettre a son emplacement.
};