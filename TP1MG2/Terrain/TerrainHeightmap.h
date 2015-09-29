#pragma once
#include "Terrain.h"
class TerrainHeightmap : public Terrain
{
	Vector3 ** pointList;
public:
	TerrainHeightmap(QImage heightmap, bool blackIsHigh, double fact);
	Vector3 getPoint(double x, double y) const;
	//bool inside(const Vector3 & p) const
	//{
	//	return Terrain::inside(p);
	//}
	//// calcul la distance en hauteur entre le point p et le terrain
	//double distance(const Vector3 & p) const
	//{
	//	return Terrain::distance(p);
	//}

	//Vector3 getColor(const Vector3 & p) const
	//{
	//	return Terrain::getColor(p);
	//}
	// Desctructeur. Désalloue pointList.
	~TerrainHeightmap();
};

