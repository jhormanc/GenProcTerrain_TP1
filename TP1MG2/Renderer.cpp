#include "Renderer.h"
#include "Sphere.h"

Renderer::Renderer(const int& width_scrn_, const int& height_scrn_, const Camera& c_, const Vector3& light_, const Terrain& t_) :
	width_scrn(width_scrn_), 
	height_scrn(height_scrn_), 
	c(c_), 
	light(light_), 
	t(t_), 
	screen(QImage(width_scrn_, height_scrn_, QImage::Format::Format_RGB32))
{

}

// renvoi l'image sur laquelle la fct raytrace dessine.
const QImage& Renderer::getScreen()
{
	return screen;
}

Renderer::~Renderer() 
{

}