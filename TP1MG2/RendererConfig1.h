#pragma once
#include "Renderer.h"
#include "../Terrain/TerrainFractal.h"

class RendererConfig1 : public Renderer
{
public:
	RendererConfig1() :Renderer(800, 600,
		Camera(Vector3(1000., 1000., 300.), Vector3(width_scrn / 2., height_scrn / 2., 0.), 1., Vector3(0., 0., -1.)),
		Vector3(1500., 1800., 400.),
		new TerrainFractal(1000, 1000, 10.0, 15.0, 255.0)){};

	~RendererConfig1()
	{
		delete t;
	}
};