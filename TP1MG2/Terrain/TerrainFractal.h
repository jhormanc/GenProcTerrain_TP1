#pragma once
#include "Terrain.h"
#include "Noise.h"
class TerrainFractal : public Terrain
{
public:
	// Renvoi un terrain g�ner� al�atoirement
	 TerrainFractal(uint terrain_width_, uint terrain_height_);
	 Vector3 getPoint(double x, double y) const;
};