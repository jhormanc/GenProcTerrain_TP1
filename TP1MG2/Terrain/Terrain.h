#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Box.h"
#include "Mesh.h"
#include "Constante.h"
#include <qimage>
#include <qpixmap>
#include <qrect>
#include <math.h>

// Classe représentant un Terrain 3D.
class Terrain {
protected:
	uint terrain_width;
	uint terrain_height;
	double step_x;
	double step_y;
	Box* boxlimit;
	double k;  // Pente maximale
	double high, low; // Paramètre pour connaître la hauteur max et min de la map
	
	
public:

	Terrain(){};
	//Pour définir un max et un min
	void MaxMin(float);
	
	// Renvoie le point x, y, z appartenant à pointList à partir du x, y (recherche matrice + interpolation).
	virtual Vector3 getPoint(double x, double y) const = 0;
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

	double getLow() const
	{
		return low;
	}

	double getHigh() const
	{
		return high;
	}
	// Calcul la pente maximale du terrain
	void calcK();
	
	// Renvoi la normal du terrain au point p
	Vector3 normal(Vector3 p);
	

	Mesh* GetMesh();

	Vector3 getColor(double x, double y);

	virtual ~Terrain(){};
	Vector3 normalT(Vector3 a, Vector3 b, Vector3 c);
};