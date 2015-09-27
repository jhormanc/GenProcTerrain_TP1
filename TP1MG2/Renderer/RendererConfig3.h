#pragma once
#include "Renderer.h"
#include "../../Terrain/TerrainHeightmap.h"

class RendererConfig3 : public Renderer
{
public:
	RendererConfig3() :Renderer(1280, 720,
		Camera(Vector3(1500., 1080., 600.), Vector3(1500, 540., 0.), 1., Vector3(0., 0., -1.)),
		Vector3(500., 500., 1000.), // Midi
		//Vector3(-100., 1100., 500.), // Couché de soleil
		new TerrainHeightmap(QImage("Resources/world_small.png"), false, 0.1)){};

	~RendererConfig3()
	{
		delete t;
	}
};