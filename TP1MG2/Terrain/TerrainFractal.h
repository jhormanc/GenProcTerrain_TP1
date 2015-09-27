#pragma once
#include "Terrain.h"
#include "Noise.h"
class TerrainFractal : public Terrain
{
public:
	// Renvoi un terrain géneré aléatoirement
	 TerrainFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z);
	 ~TerrainFractal(){};
};