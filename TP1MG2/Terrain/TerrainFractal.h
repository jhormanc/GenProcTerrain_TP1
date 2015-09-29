#pragma once
#include "Terrain.h"
#include "Noise.h"
class TerrainFractal : public Terrain
{
public:
	// Renvoi un terrain géneré aléatoirement
	 TerrainFractal(uint terrain_width_, uint terrain_height_);
	 Vector3 getPoint(double x, double y) const;
	 /*
	 // Renvoie vrai si le point p est en dehors du terrain, faux sinon.
	 bool inside(const Vector3 & p) const
	 {
		return Terrain::inside(p);
	 }
	 // calcul la distance en hauteur entre le point p et le terrain
	  double distance(const Vector3 & p) const
	 {
		 return Terrain::distance(p);
	 }

	  Vector3 getColor(const Vector3 & p) const
	 {
		 return Terrain::getColor(p);
	 } */
};