#include "Renderer.h"
#include "../Sphere.h"

Renderer::Renderer(const int& width_scrn_, const int& height_scrn_, const Camera& c_, const Vector3& light_, Primitive * p_) :
	width_scrn(width_scrn_), 
	height_scrn(height_scrn_), 
	c(c_), 
	light(light_), 
	p(p_), 
	screen(QImage(width_scrn_, height_scrn_, QImage::Format::Format_RGB32))
{

}

Renderer::~Renderer()
{
	delete p;
}

// renvoi l'image sur laquelle la fct raytrace dessine.
const QImage& Renderer::getScreen()
{
	return screen;
}

// Raytrace le terrain sur l'image screen grace aux differents objets du constructeur.


// Raytrace le terrain sur l'image screen grace aux differents objets du constructeur.
void Renderer::Raytrace()
{
	double f;
	double eps = 10.;
	// Sun
	//double s;
	float rayon = 50.;
	Sphere sun(light, rayon);


	for (int i = 0; i < width_scrn; i++)
	{
		for (int j = 0; j < height_scrn; j++)
		{

			Vector3 cam_dir = Vector3::normalize(c.PtScreen(i, j, width_scrn, height_scrn) - c.getOrigin());
			Ray r = Ray(c.getOrigin(), cam_dir);

			// Intersection entre la vue (camera) et l'objet.
			p->intersect(r, f);
			Vector3 intersect(r.getOrigin() + r.getDirection() * abs(f));

			if (f > Constante::noIntersect) // Si intersection
			{
				// Vecteur directeur du point d'intersection vers la lumiere
				Vector3 dir = Vector3::normalize(intersect - light);

				Ray ray(light, dir);
				p->intersect(ray, f);

				Vector3 intersect_light(ray.getOrigin() + ray.getDirection() * abs(f));
				intersect_light = intersect_light + dir * eps;

				// Si l'intersection lumiere / objet se fait avant l'intersection camera / objet
				if (f > Constante::noIntersect && Vector3::distance(light, intersect_light) + eps < Vector3::distance(light, intersect)) //"+eps" pour l'imperfection des flotant
				{
					double fact = 0.2;
					Vector3 color = p->getColor(intersect);// = s->getColor(intersect.x, intersect.y);

					// Pixel d'intersection camera/objet represente l'ombre
					screen.setPixel(i, j, qRgb(color.x*fact, color.y*fact, color.z*fact));
				}
				else{

					double fact = 1.0;
					Vector3 color = p->getColor(intersect);// = s->getColor(intersect.x, intersect.y);

					// Pixel d'intersection camera/objet represente l'ombre
					screen.setPixel(i, j, qRgb(color.x*fact, color.y*fact, color.z*fact));
					/*Diffusion*/
					/*Vector3 L = Vector3::normalize(light - intersect);
					Vector3 N = p->normal(intersect);
					double colorDiffuse = L*N; 
					colorDiffuse = std::abs(colorDiffuse) / Constante::pi * 2 + 0.1;

					Vector3 color(255);

					// Représente lumière 
					screen.setPixel(i, j, qRgb(color.x * colorDiffuse, color.y * colorDiffuse, color.z * colorDiffuse)); */


				}


			}
			else
			{
				screen.setPixel(i, j, qRgb(155, 255, 255)); // aucun contact avec le terrain ou la lumiere.
				//}
			}
		}
	}
}