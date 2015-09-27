#pragma once
#include "Renderer.h"
#include "../../Terrain/TerrainHeightmap.h"

class RendererConfig4 : public Renderer
{
public:
	RendererConfig4() :Renderer(1280, 720,
		//Camera(Vector3(1080., 1080., 600.), Vector3(1080, 540., 0.), 1., Vector3(0., 0., -1.)), // Full
		Camera(Vector3(16600, 5500., 100.), Vector3(16600., 4000., 0.), 1., Vector3(0., 0., -1.)), // Zoom
		Vector3(21600., 10800., 500.), // Midi
		//Vector3(-100., 1100., 500.), // Couche de soleil
		new TerrainHeightmap(QImage("Resources/world.png"), false, 0.1)){};

	~RendererConfig4()
	{
		delete t;
	}
};