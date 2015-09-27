#include "TerrainHeightmap.h"

TerrainHeightmap::TerrainHeightmap(QImage heightmap, bool blackIsHigh, double fact) :Terrain()
{
	int height = heightmap.height();
	int width = heightmap.width();
	pointList = new Vector3 *[width];
	for (int i = 0; i < width; i++)
		pointList[i] = new Vector3[height];

	terrain_height = height;
	terrain_width = width;
	
	QColor it = (heightmap.pixel(0, 0));
	double gray = blackIsHigh ? 255 - ((it.red() + it.blue() + it.green()) / 3) : ((it.red() + it.blue() + it.green()) / 3);

	high = gray * fact;
	low = gray * fact;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{

			it = (heightmap.pixel(i, j));
			gray = blackIsHigh ? 255 - ((it.red() + it.blue() + it.green()) / 3) : ((it.red() + it.blue() + it.green()) / 3);
			pointList[i][j] = Vector3(i, j, gray * fact);
			
			MaxMin(gray * fact);
		}
	}

	calcK();
}

// Renvoi le point x, y, z appartenant à pointList à partir du x, y (recherche matrice + interpolation).
Vector3 TerrainHeightmap::getPoint(double x, double y) const
{
	int tmpI = (int)x;
	int tmpJ = (int)y;

	if (!(tmpI < terrain_width && tmpJ < terrain_height))
		return Constante::noIntersectVec;

	Vector3 & a(pointList[tmpI < terrain_width - 1 ? tmpI + 1 : tmpI][tmpJ]);
	Vector3 & b(pointList[tmpI][tmpJ < terrain_width - 1 ? tmpJ + 1 : tmpJ]);
	Vector3 & c(pointList[tmpI < terrain_width - 1 ? tmpI + 1 : tmpI][tmpJ < terrain_width - 1 ? tmpJ + 1 : tmpJ]);

	double x2 = x - (double)tmpI;
	double y2 = y - (double)tmpJ;
	double z = (1 - x2) * (1 - y2) * pointList[tmpI][tmpJ].z
		+ x2 * (1 - y2) * a.z
		+ (1 - x2) * y2 * b.z
		+ x2 * y2 * c.z;

	return Vector3(x, y, z);
}

TerrainHeightmap::~TerrainHeightmap()
{
	for (int i = 0; i < terrain_width; ++i)
		delete[] pointList[i];
	delete[] pointList;
}