#pragma once
#include "Terrain.h"
class TerrainHeightmap : public Terrain
{
	Vector3 ** pointList;
public:
	TerrainHeightmap(QImage heightmap);
	inline Vector3 getPoint(double x, double y) const
	{
		int tmpI = (int)x;
		int tmpJ = (int)y;

		if (!(tmpI < terrain_width && tmpJ < terrain_height))
		{
			return Constante::noIntersectVec;
		}
		Vector3 & a(pointList[tmpI < terrain_width - 1 ? tmpI + 1 : tmpI][tmpJ]);
		Vector3 & b(pointList[tmpI][tmpJ < terrain_width - 1 ? tmpJ + 1 : tmpJ]);
		Vector3 & c(pointList[tmpI < terrain_width - 1 ? tmpI + 1 : tmpI][tmpJ < terrain_width - 1 ? tmpJ + 1 : tmpJ]);

		double x2 = x - tmpI;
		double y2 = y = tmpJ;
		double z = (1 - x2) * (1 - y2) * pointList[tmpI][tmpJ].z
			+ x2 * (1 - y2) * a.z
			+ (1 - x2) * y2 * b.z
			+ x2 * y2 * c.z;



		return Vector3(x, y, z);
	}


		// Desctructeur. Desalloue pointList.
	~TerrainHeightmap();
};

