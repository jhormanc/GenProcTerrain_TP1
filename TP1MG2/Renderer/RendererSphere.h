#pragma once
#include "Renderer.h"
#include "../../CSG/CSG_Sphere.h"
#include "../../CSG/CSG_Box.h"
#include "../../OpBinaire/Union.h"
#include "../../OpBinaire/Intersection.h"
#include "../../OpBinaire/Difference.h"

class RendererSphere : public Renderer
{
public:
	RendererSphere() :Renderer(1280, 720,
	Camera(Vector3(-20., 800., 500.), Vector3(500., 400., 0.), 1., Vector3(0., 0., -1.)),
	//Vector3(500., 500., 1000.), // Midi
	Vector3(-100., 1100., 500.), // Couche de soleil
	new Difference(new CSG_Box(Vector3(400., 400., 0.), Vector3(100.)), new CSG_Sphere(Vector3(400., 400., 0.), 120., Vector3(0., 0., 204.)))){};
};