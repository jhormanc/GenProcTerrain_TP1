#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Mesh.h"
#include "Constante.h"
#include "Primitive.h"
#include <qimage>
#include <qpixmap>
#include <qrect>
#include <math.h>

// Classe representant un Terrain 3D.
class Terrain : public Primitive{
protected:
	uint terrain_width;
	uint terrain_height;
	double k;  // Pente maximale
	double high, low; // Paramètre pour connaitre la hauteur max et min de la map
	
	

public:

	Terrain():Primitive(){};
	//Pour definir un max et un min
	void MaxMin(double);
	
	// Renvoie vrai si le point p est en dehors du terrain, faux sinon.
	virtual bool inside(const Vector3 & p) const;
	// calcul la distance en hauteur entre le point p et le terrain
	virtual double distance(const Vector3 & p) const;

	virtual Vector3 getColor(const Vector3 & p) const;
	
	// Renvoi la normal du terrain au point p
	virtual Vector3 normal(const Vector3 & ) const;

	// Renvoie le point x, y, z appartenant a pointList a partir du x, y (recherche matrice + interpolation).
	virtual Vector3 getPoint(double x, double y) const = 0	;



	
	// Renvoie vrai si le Ray r touche le terrain.
//	bool intersection(Ray r, double &t) const;
	
	// DEBUG
	uint getWidth() const
	{
		return terrain_width;
	}
	uint getHeight() const
	{
		return terrain_height;
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
	

	Mesh* GetMesh();


	virtual ~Terrain(){};
};