#pragma once
#include "Renderer.h"
#include "../Terrain/TerrainFractal.h"

class RendererConfig1 : public Renderer
{
public:
	RendererConfig1() :Renderer(1280, 720,
		Camera(Vector3(-20., -20., 700.), Vector3(500., 500., 0.), 1., Vector3(0., 0., -1.)),
		//Vector3(500., 500., 1000.), // Midi
		Vector3(-100., 1100., 500.), // Couché de soleil
		new TerrainFractal(1000, 1000, 1.0, 1.0, 255.0)){};

	~RendererConfig1()
	{
		delete t;
	}
};