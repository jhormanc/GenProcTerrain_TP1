#include "TerrainFractal.h"
// Renvoi un terrain genere al�atoirement
TerrainFractal::TerrainFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z)
{
	double facteur = max_z; // On veut que les montagnes d�passent pour pouvoir faire le ridge.
	terrain_width = terrain_width_;
	terrain_height = terrain_height_;
	double z;
	hight = (low = Noise::noise(0, 0));
	/**Pour recuperer le Low and Hight**/
	for (int j = 0; j < terrain_height_; j++)
	{
		for (int i = 0; i < terrain_width_; i++)
		{
			double x = i;
			double y = j;

			z = Noise::noise(i, j);
			hight = std::max(hight, z);
			low = std::min(low, z);


		}
	}
}