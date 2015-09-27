#pragma once
#include<chrono>
#include <iostream>
#include <fstream>
#include "Renderer/Renderer.h"
#include "Renderer/RendererConfig1.h"
#include "Renderer/RendererConfig2.h"
// Class qui execute et note les mesures.
class Mesure {
	
public:
	Mesure(){};
	void execMesure() const;
};