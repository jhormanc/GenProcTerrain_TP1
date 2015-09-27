#pragma once
#include "Terrain.h"
#include "Noise.h"
class TerrainFractal : public Terrain
{
public:
	// Renvoi un terrain géneré aléatoirement
	 TerrainFractal(uint terrain_width_, uint terrain_height_, double max_z);
	 Vector3 getPoint(double x, double y) const;
};