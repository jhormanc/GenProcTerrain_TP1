#pragma once
#include "Renderer\Renderer.h"
#include "../CSG/CSG_Cylinder.h"
#include "../Vector2.h"
class RendererCylinder : public Renderer
{
public:
	RendererCylinder() :Renderer(1280, 720,
		Camera(Vector3(-20., 800., 800.), Vector3(500., 800., 0.), 1., Vector3(0., 0., -1.)),
		//Vector3(500., 500., 1000.), // Midi
		Vector3(-100., 1100., 500.), // Couche de soleil
		new Rotation(new Translation(new CSG_Cylinder(Vector3(0., 0., 0.), Vector2(200., 400.)), Vector3(400., 400., 0.)), Vector3(0., Constante::pi, 0.))){};
};