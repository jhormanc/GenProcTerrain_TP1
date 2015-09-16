#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <qimage>
#include <qpixmap>
#include <qrect>
#include <math.h>

#define BIG_DOUBLE 43758.5453123
// Classe représentant un Terrain 3D.
class Terrain {

	Vector3 ** pointList;
	uint terrain_width;
	uint terrain_height;
	uint step_x;
	uint step_y;

	// Renvoi une valeur aleatoire entre 0 et 1 a partir de x.
	static double hash(double x);
public:
	// Constructeur.
	Terrain(const Terrain& t);
	Terrain(QImage heightmap, uint terrain_width_, uint terrain_height_, double step_x_, double step_y_);
	Terrain(Vector3 ** pointList_, uint terrain_width_, uint terrain_height_, double step_x_, double step_y_) : pointList(pointList_), terrain_height(terrain_height_), terrain_width(terrain_width_), step_x(step_x_), step_y(step_y_){};

	// Renvoi un terrain genere aléatoirement
	static Terrain CreateRidgeFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z);
	// Renvoi le point x, y, z appartenant a pointList a partir du x, y (recherche matrice + interpolation).
	Vector3 getPoint(double x, double y) const;
	// Renvoie vrai si le point p est en dehors du terrain, faux sinon.
	bool inOut(Vector3 p) const;

	// Renvoie vrai si le Ray r touche le terrain.
	bool instersection(Ray r, double &t) const;
	
	// DEBUG
	uint getWidth() const
	{
		return terrain_width;
	}
	uint getHeight() const
	{
		return terrain_height;
	}
	uint getStepX() const
	{
		return step_x;
	}
	uint getStepY() const
	{
		return step_y;
	}
	Vector3 ** getPointList()
	{
		return pointList;
	}

	// Desctructeur. Desalloue pointList.
	~Terrain();
};