#include "TerrainFractal.h"
// Renvoi un terrain généré aléatoirement
TerrainFractal::TerrainFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z)
{
	double facteur = max_z; // On veut que les montagnes dépassent pour pouvoir faire le ridge.
	terrain_width = terrain_width_;
	terrain_height = terrain_height_;
	double z = (low = Noise::noise(0, 0));
	high = z;
	low = z;
	pointList = new Vector3 *[terrain_width];
	for (int i = 0; i < terrain_width; i++)
		pointList[i] = new Vector3[terrain_height];

	// Pour récuperer le Low and Height
	for (int j = 0; j < terrain_height_; j++)
	{
		for (int i = 0; i < terrain_width_; i++)
		{
			double x = i;
			double y = j;

			z = Noise::noise(i, j);

			pointList[i][j] = z;

			MaxMin(z);
		}
	}

	calcK();
}