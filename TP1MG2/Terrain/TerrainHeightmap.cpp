#include "TerrainHeightmap.h"

TerrainHeightmap::TerrainHeightmap(QImage heightmap) :Terrain()
{
	int height = heightmap.height();
	int width = heightmap.width();
	pointList = new Vector3 *[width];
	for (int i = 0; i < width; i++)
		pointList[i] = new Vector3[height];

	terrain_height = height;
	terrain_width = width;
	double fact = 1.;
	
	QColor it = (heightmap.pixel(0, 0));
	double gray = 255 - ((it.red() + it.blue() + it.green()) / 3);

	high = gray * fact;
	low = gray * fact;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{

			it = (heightmap.pixel(i, j));
			gray = 255 - ((it.red() + it.blue() + it.green()) / 3);
			pointList[i][j] = Vector3(i, j, gray * fact);
			
			MaxMin(gray * fact);
		}
	}

	calcK();
}


TerrainHeightmap::~TerrainHeightmap()
{
	for (int i = 0; i < terrain_width; ++i)
		delete[] pointList[i];
	delete[] pointList;
}