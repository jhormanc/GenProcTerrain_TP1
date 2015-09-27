#pragma once
#include "Renderer.h"
#include "../../Terrain/TerrainHeightmap.h"

class RendererConfig3 : public Renderer
{
public:
	RendererConfig3() :Renderer(1280, 720,
		Camera(Vector3(1080., 1080., 600.), Vector3(1080, 540., 0.), 1., Vector3(0., 0., -1.)), // Full
		//Camera(Vector3(1660, 550., 100.), Vector3(1660., 400., 0.), 1., Vector3(0., 0., -1.)), // Zoom
		//Camera(Vector3(1500., 1080., 600.), Vector3(1500, 540., 0.), 1., Vector3(0., 0., -1.)),
		Vector3(1080, 540, 200.), // Midi
		//Vector3(-100., 1100., 500.), // Couche de soleil
		new TerrainHeightmap(QImage("Resources/world_small.png"), false, 0.1)){};
};