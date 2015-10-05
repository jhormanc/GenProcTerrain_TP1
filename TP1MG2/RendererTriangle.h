#pragma once
#include "Renderer\Renderer.h"
#include "../CSG_Triangle.h"
class RendererTriangle : public Renderer
{
public:
	RendererTriangle() :Renderer(1280, 720,
		Camera(Vector3(-20., 800., 800.), Vector3(500., 800., 0.), 1., Vector3(0., 0., -1.)),
		//Vector3(500., 500., 1000.), // Midi
		Vector3(-100., 1100., 500.), // Couche de soleil
		new CSG_Triangle(Vector3(200., 200., 200.), Vector3(-200., 200., 200.),Vector3(0., 400., 200.))){};
};