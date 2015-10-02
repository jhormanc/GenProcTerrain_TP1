#pragma once
#include "Renderer.h"
#include "../../Terrain/TerrainFractal.h"

class RendererConfig5 : public Renderer
{
public:
	RendererConfig5() : Renderer(1280, 720,
		Camera(Vector3(-200., 1000., 900.), Vector3(1200., 1000., 0.), 1., Vector3(0., 0., -1.)),
		Vector3(1000., 1000., 1100.), // Midi
		//Vector3(-100., 1100., 500.), // Couche de soleil
		new TerrainFractal(2000, 2000)){};

};