#pragma once
#include "Vector3.h"

class Box
{
private:
	Vector3 P1, // Point right bottom
		P2; // Point left top

public:
	Box(void);
	Box(Vector3, Vector3);

	// Accessor
	Vector3 getP1() const
	{
		return P1;
	}

	Vector3 getP2() const
	{
		return P2;
	}

	~Box(void);
};

