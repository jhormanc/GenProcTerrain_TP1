#include "Renderer.h"
#include "Sphere.h"

Renderer::Renderer(const int& width_scrn_, const int& height_scrn_, const Camera& c_, const Vector3& light_, Terrain * t_) :
	width_scrn(width_scrn_), 
	height_scrn(height_scrn_), 
	c(c_), 
	light(light_), 
	t(t_), 
	screen(QImage(width_scrn_, height_scrn_, QImage::Format::Format_RGB32))
{

}

Renderer::~Renderer()
{

}

// renvoi l'image sur laquelle la fct raytrace dessine.
const QImage& Renderer::getScreen()
{
	return screen;
}

// Raytrace le terrain sur l'image screen grace aux differents objets du constructeur.
void Renderer::Raytrace()
{
	double f;
	double eps = 10.;
	// Sun
	double s;
	float rayon = 50.;
	Sphere sun(light, rayon);


	for (int i = 0; i < width_scrn; i++)
	{
		for (int j = 0; j < height_scrn; j++)
		{
			Vector3 pt(c.PtScreen(i, j, width_scrn, height_scrn));
			Vector3 cam_dir = Vector3::normalize(pt - c.getOrigin());
			Ray r = Ray(c.getOrigin(), cam_dir);

			// Intersection entre la vue (caméra) et l'objet.
			t->intersection(r, f); 
			Vector3 intersect(r.getOrigin() + r.getDirection() * abs(f));

			if (f > Constante::noIntersect && intersect.z >= t->getLow()) // Si intersection
			{
				// Vecteur directeur du point d'intersection vers la lumière
				Vector3 dir = Vector3::normalize(intersect - light);

				// Règle l'imprécision des flottants en décalant d'epsilon le point d'intersection vers la lumière
				intersect = intersect + cam_dir * eps;

				Ray ray(light, dir);
				t->intersection(ray, f);

				Vector3 intersect_light(ray.getOrigin() + ray.getDirection() * abs(f));
				intersect_light = intersect_light + dir * eps;

				// Si l'intersection lumière / objet se fait avant l'intersection caméra / objet
				if (f > Constante::noIntersect && Vector3::distance(light, intersect_light) < Vector3::distance(light, intersect))
				{
					double fact = 0.2;
					Vector3 color = t->getColor(intersect.x, intersect.y);

					// Pixel d'intersection caméra/objet représente l'ombre
					screen.setPixel(i, j, qRgb(color.x*fact, color.y*fact, color.z*fact)); 
					// DEBUG
					//screen.setPixel(i,j,qRgb(255.,255.,0.)); 
				}
				else{

					/*Diffu v2*/
					Vector3 L = Vector3::normalize(light - intersect);
					Vector3 N = t->normal(intersect);
					double colorDiffuse = L*N;
					colorDiffuse = std::abs(colorDiffuse) / Constante::pi * 2 + 0.1;

					Vector3 color = t->getColor(intersect.x, intersect.y);

					// Représente lumière 
					screen.setPixel(i, j, qRgb(color.x * colorDiffuse, color.y * colorDiffuse, color.z * colorDiffuse)); 


				}


			}
			else
			{
				// Sun
				//Ray ray_sun = Ray(c.getOrigin(), Vector3::normalize(pt - c.getOrigin()));
				//sun.intersection(r, s); // Intersection entre la vue (caméra) et la lumière.

				//if (s > Constante::noIntersect)
				//{
				//	Vector3 pt_sun(r.getOrigin() + r.getDirection() * abs(s));
				//	screen.setPixel(i, j, qRgb(255., 255., 0.));
				//}
				//else
				//{
				screen.setPixel(i, j, qRgb(155, 255, 255)); // aucun contact avec le terrain ou la lumière.
				//}
			}

			// Sun
			//Ray ray_sun = Ray(c.getOrigin(), Vector3::normalize(pt - c.getOrigin()));
			sun.intersection(r, s); // Intersection entre la vue (caméra) et la lumière.

			if (s > Constante::noIntersect)
			{
				Vector3 pt_sun(r.getOrigin() + r.getDirection() * abs(s));
				screen.setPixel(i, j, qRgb(255., 255., 0.));
			}
		}
	}
}