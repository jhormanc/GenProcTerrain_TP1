#pragma once
#include "Renderer.h"
#include "../../CSG_Sphere.h"
#include "../../Union.h"

class RendererSphere : public Renderer
{
public:
	RendererSphere() :Renderer(1280, 720,
	Camera(Vector3(-20., 800., 800.), Vector3(500., 800., 0.), 1., Vector3(0., 0., -1.)),
	//Vector3(500., 500., 1000.), // Midi
	Vector3(-100., 1100., 500.), // Couche de soleil
	new Union(new CSG_Sphere(Vector3(400., 400., 0.), 100.), new CSG_Sphere(Vector3(450., 450., 0.), 100.))){};
};