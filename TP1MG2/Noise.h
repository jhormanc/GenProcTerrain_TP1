#pragma once

#include "Vector3.h"

class Noise
{
public:
	static double noise(const double x, const double y);
	static double ridge(const double z, const double zr);

private:
	static double noise1(const double x, const double y);
	static double noise2(const double x, const double y);

	static int fastfloor(double x);
	static double dot(int g[], double x, double y);

	// Renvoi une valeur aleatoire entre 0 et 1 a partir de x.
	static double hash(double x);
	static Vector3 warp(const Vector3 p, const double c, const double f, const bool perlin);
	static double smooth(const double z, const double zmin, const double zmax);

	static double perlin2D(const double x, const double y);
	static double simplex(const double xin, const double yin);
};

