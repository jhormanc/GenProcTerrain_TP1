#include "TerrainFractal.h"
// Renvoi un terrain g�n�r� al�atoirement
TerrainFractal::TerrainFractal(uint terrain_width_, uint terrain_height_)
{
	terrain_width = terrain_width_;
	terrain_height = terrain_height_;
	high = (low = Noise::noise(0, 0));

	// Pour r�cuperer le Low and Height
	for (uint j = 0; j < terrain_height; j++)
	{
		for (uint i = 0; i < terrain_width; i++)
		{
			MaxMin(Noise::noise(i, j));
		}
	}

	calcK();
}

Vector3 TerrainFractal::getPoint(double x, double y) const
{
	return x > 0 && x < terrain_width && y > 0 && y < terrain_height ? Vector3(x, y, Noise::noise(x, y)) : Constante::noIntersectVec;
}