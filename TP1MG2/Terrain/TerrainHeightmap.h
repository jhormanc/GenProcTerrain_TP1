#pragma once
#include "Terrain.h"
class TerrainHeightmap : public Terrain
{
	Vector3 ** pointList;
public:
	TerrainHeightmap(QImage heightmap, bool blackIsHigh, double fact);
	Vector3 getPoint(double x, double y) const;
	// Desctructeur. Désalloue pointList.
	~TerrainHeightmap();
};

