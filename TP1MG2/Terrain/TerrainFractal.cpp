#include "TerrainFractal.h"
// Renvoi un terrain généré aléatoirement
TerrainFractal::TerrainFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z)
{
	double facteur = max_z; // On veut que les montagnes dépassent pour pouvoir faire le ridge.
	terrain_width = terrain_width_;
	terrain_height = terrain_height_;
	double z;
	high = (low = Noise::noise(0, 0));

	// Pour récuperer le Low and Height
	for (int j = 0; j < terrain_height; j++)
	{
		for (int i = 0; i < terrain_width; i++)
		{
			double x = i;
			double y = j;

			z = Noise::noise(i, j);

			MaxMin(z);
		}
	}

	calcK();
}

Vector3 TerrainFractal::getPoint(double x, double y) const
{
	return x > 0 && x < terrain_width && y > 0 && y < terrain_height ? Vector3(x, y, Noise::noise(x, y)) : Constante::noIntersectVec;
}