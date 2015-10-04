#pragma once
#include "Renderer.h"
#include "../../CSG_Sphere.h"
#include "../../Union.h"
#include "../../OpUnaire/Translation.h"
#include "../../OpUnaire/Rotation.h"
#include "../../OpUnaire/Scale.h"
#include "../../Constante.h"

class RendererOpUnaire : public Renderer
{
public:
	RendererOpUnaire() :Renderer(1280, 720,
		Camera(Vector3(-20., 800., 800.), Vector3(500., 800., 0.), 1., Vector3(0., 0., -1.)),
		//Vector3(500., 500., 1000.), // Midi
		Vector3(-100., 1100., 500.), // Couche de soleil
		new Rotation(new Scale
		(new Translation
		(new Union
		(new CSG_Sphere(Vector3(400., 400., 0.), 100.),
		new CSG_Sphere(Vector3(450., 450., 0.), 100.)),
		Vector3(10., 40., 0.)),
		2.),
		Vector3(Constante::pi, 0., 0.))){};
};