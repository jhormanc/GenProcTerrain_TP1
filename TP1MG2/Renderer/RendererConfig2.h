#pragma once
#include "Renderer.h"
#include "../../Terrain/TerrainHeightmap.h"

class RendererConfig2 : public Renderer
{
public:
	RendererConfig2() :Renderer(1280, 720,
		Camera(Vector3(-20., 800., 800.), Vector3(500., 800., 0.), 1., Vector3(0., 0., -1.)),
		//	Vector3(500., 500., 1000.), // Midi
		Vector3(-100., 1100., 500.), // Couché de soleil
		new TerrainHeightmap(QImage("Resources/Heightmap2.png"), true, 1.)){};

};