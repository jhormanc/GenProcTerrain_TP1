#include "Mesure.h"
void Mesure::execMesure() const
{
	Renderer * r1 = new RendererConfig1();
	Renderer * r2 = new RendererConfig2();
	std::ofstream mesureFile("mesureFile.txt", std::ios::out | std::ios::trunc);
	std::chrono::high_resolution_clock timer;
	auto start = timer.now();
	auto end = timer.now();


	start = timer.now();
	r1->Raytrace();
	end = timer.now();
	mesureFile << "Raytracage Fractal : " << std::chrono::nanoseconds(end - start).count()<< std::endl;
	start = timer.now();
	r2->Raytrace();
	end = timer.now();
	mesureFile << "Raytracage Heightmap : " << std::chrono::nanoseconds(end - start).count() << std::endl;
	mesureFile.close();

	delete r1;
	delete r2;
}