#pragma once
#include "Renderer.h"
#include "../../CSG_Sphere.h"

class RendererConfig4 : public Renderer
{
public:
	RendererConfig4() :Renderer(1280, 720,
	Camera(Vector3(-20., 800., 800.), Vector3(500., 800., 0.), 1., Vector3(0., 0., -1.)),
	Vector3(500., 500., 1000.), // Midi
	Vector3(-100., 1100., 500.), // Couche de soleil
	new CSG_Sphere(Vector3(400., 400., 0.), 100.));
};