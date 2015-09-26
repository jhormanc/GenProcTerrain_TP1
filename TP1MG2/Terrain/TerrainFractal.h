#pragma once
#include "Terrain.h"
#include "Noise.h"
class TerrainFractal : public Terrain
{
public:
	// Renvoi un terrain genere al�atoirement
	 TerrainFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z);
	 // Renvoi le point x, y, z appartenant a pointList a partir du x, y (recherche matrice + interpolation).
	 inline Vector3 getPoint(double x, double y) const
	 {

		 return (x < terrain_width && y < terrain_height && x > 0 && y > 0) ?
			 Noise::noise(x, y) :
			 Constante::noIntersectVec;
	 }
	 ~TerrainFractal(){};
};