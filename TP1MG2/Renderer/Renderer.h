#pragma once

#include "../Vector3.h"
#include "../Ray.h"
#include "../Camera.h"
#include "../../Terrain/Terrain.h"
#include "../Constante.h"
#include "../Primitive.h"

// Classe s'occupant du rendu
class Renderer
{
protected:
	int width_scrn;
	int height_scrn;
	Camera c;
	Vector3 light;
	Primitive *p;
	QImage screen;

public:
	Renderer(const int& width_scrn_, const int& height_scrn_, const Camera& c_, const Vector3& light_, Primitive *p_);

	// Raytrace le terrain sur l'image screen grace aux differents objets du constructeur.
	void Raytrace();
	
	const QImage& getScreen();

	virtual ~Renderer();
};

