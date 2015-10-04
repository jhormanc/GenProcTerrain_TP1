#pragma once
#include "opunaire.h"
#include "Node.h"
#include <algorithm>
#include "Mat3x3.h"
class Rotation :
	public OpUnaire
{
private:
	Vector3 rotate;
	Mat3x3 RxT;
	Mat3x3 RyT;
	Mat3x3 RzT;
public:
	Rotation(void) : OpUnaire() {}
	Rotation(Node *p_, Vector3 rotate_) : OpUnaire(p_), rotate(rotate_), RxT(Rotation::calcRxT(rotate_.x)), RyT(Rotation::calcRyT(rotate_.y)), RzT(Rotation::calcRzT(rotate_.z)){} // Pour depanner normalement pas Node et pas Primitives
	~Rotation(void);

	bool inside(const Vector3 &p) const
	{
		return n->inside((RzT * (RyT * (RxT * (p - n->getOrigin())))) + n->getOrigin());
	}

	double distance(const Vector3 &p) const
	{
		return n->distance((RzT * (RyT * (RxT * (p - n->getOrigin())))) + n->getOrigin());
	}

	Vector3 normal(const Vector3 &p) const
	{
		return n->normal((RzT * (RyT * (RxT * (p - n->getOrigin())))) + n->getOrigin());
	}

	Vector3 getColor(const Vector3 &p) const
	{
		return n->getColor((RzT * (RyT * (RxT * (p - n->getOrigin())))) + n->getOrigin());
	}

	Vector3 getOrigin() const
	{
		return n->getOrigin();//n->getOrigin();
	}

	// transposee de la matrice rotation x d'angle car pour matrice rotation, inverse = transposee.
	static Mat3x3 calcRxT(double angle)
	{
		return Mat3x3(Vector3(1., 0., 0.),
					  Vector3(0., cos(angle), sin(angle)),
					  Vector3(0., - sin(angle), cos(angle)));
	}

	static Mat3x3 calcRyT(double angle)
	{
		return Mat3x3(Vector3(cos(angle), 0., -sin(angle)),
					 Vector3(0., 1., 0.),
					 Vector3(sin(angle), 0., cos(angle)));
	}

	static Mat3x3 calcRzT(double angle)
	{
		return Mat3x3(Vector3(cos(angle), sin(angle), 0.),
			Vector3(-sin(angle), cos(angle), 0.),
			Vector3(0., 0., 1.)
			);
	}
};
