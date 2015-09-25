#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Box.h"
#include "Mesh.h"
#include <qimage>
#include <qpixmap>
#include <qrect>
#include <math.h>

#define BIG_DOUBLE 43758.5453123
const Vector3 noneVec(-10., -10., -10.);
// Classe représentant un Terrain 3D.
class Terrain {

	Vector3 ** pointList;
	uint terrain_width;
	uint terrain_height;
	double step_x;
	double step_y;
	Box* boxlimit;
	double k;  // pente maximale (coefficient de liepz...
	float hight,low; /*Parametre pour connaitre la hauteur max et minimum de la map*/
	
public:
	// Constructeur.
	Terrain(const Terrain& t);
	Terrain(QImage heightmap, uint terrain_width_, uint terrain_height_, double step_x_, double step_y_);
	Terrain(Vector3 ** pointList_, uint terrain_width_, uint terrain_height_, double step_x_, double step_y_,float h,float l) : pointList(pointList_), terrain_height(terrain_height_), terrain_width(terrain_width_), step_x(step_x_), step_y(step_y_),hight(h),low(l){};
	Terrain(QImage,Vector3,Vector3/*,const double*,const double**/);/*Constructeur pour créer la box avec le terrain*/

	//Pour definir un max et un min
	void MaxMin(float);
	// Renvoi un terrain genere aléatoirement
	static Terrain CreateRidgeFractal(uint terrain_width_, uint terrain_height_, double step_x_, double step_y_, double max_z);
	// Renvoi le point x, y, z appartenant a pointList a partir du x, y (recherche matrice + interpolation).
	Vector3 getPoint(double x, double y) const;
	// Renvoie vrai si le point p est en dehors du terrain, faux sinon.
	bool inOut(Vector3 p) const;

	// Renvoie vrai si le Ray r touche le terrain.
	bool intersection(Ray r, double &t) const;
	
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

	double getLow() const
	{
		return low;
	}

	double getHight() const
	{
		return hight;
	}
	// calcul la pente maximale du terrain
	void calcK();
	
	// renvoi la normal du terrain au point p
	Vector3 normal(Vector3 p);
	// Desctructeur. Desalloue pointList.
	~Terrain();

	Mesh* GetMesh();
};