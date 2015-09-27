#pragma once
#include "Terrain.h"
class TerrainHeightmap : public Terrain
{
	
public:
	TerrainHeightmap(QImage heightmap);

	// Desctructeur. Désalloue pointList.
	~TerrainHeightmap();
};

