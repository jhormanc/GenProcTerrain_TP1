#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Camera.h"
#include "Terrain.h"
#include "Constante.h"

// Classe s'occupant du rendu
class Renderer
{
	int width_scrn;
	int height_scrn;
	Camera c;
	Vector3 light;
	Terrain t;
	QImage screen;
public:

	Renderer(const int& width_scrn_, const int& height_scrn_, const Camera& c_, const Vector3& light_, const Terrain& t_) : width_scrn(width_scrn_), height_scrn(height_scrn_), c(c_), light(light_), t(t_), screen(QImage(width_scrn_, height_scrn_, QImage::Format::Format_RGB32)){};
// Raytrace le terrain sur l'image screen grace aux differents objets du constructeur.
	inline void Renderer::Raytrace()
	{
		double f;
		double eps = 0.1;
		for (int i = 0; i < width_scrn; i++)
		{
			for (int j = 0; j < height_scrn; j++)
			{
				Vector3 pt(c.PtScreen(i, j, width_scrn, height_scrn));
				Ray r = Ray(c.getOrigin(), Vector3::normalize(pt - c.getOrigin()));

				t.intersection(r, f); //Intersection entre la vue ( camera ) et l'objet.
				Vector3 intersect(r.getOrigin() + r.getDirection()*(abs(f)));
				if (f > Constante::noIntersect && intersect.z >= t.getLow()) //Si intersection
				{
					//Pour avoir le point d'intersection sur la l'objet ( sphere )
					Vector3 direction = Vector3::normalize(intersect - light); //Pour avoir la direction entre la lumiére ( son origine ) et le point d'intersection sur l'object (sphere )
					Ray lightvec = Ray(light, direction); //On crée le ray.

					t.intersection(lightvec, f); //Intersection entre le ray (de la lumiére ) et l'objet ( sphere )

					Vector3 intersectlight(lightvec.getOrigin() + lightvec.getDirection()*(abs(f))); // coordonée du point d'intersection du Ray sur la sphere.
					/*Je fait un "*(-h)" car je sais pas pourquoi le h retourné est negatif*/
					//intersectlight += lightvec.getDirection()  * (eps);// regle l'imprecision des flottants en decalant d'epsilon le point d'intersection vers la lumiere
					double distance1 = Vector3::distance(lightvec.getOrigin(), intersectlight); //Distance entre lumiére ( origine ) et intersection (lumiére / object )
					double distance2 = Vector3::distance(lightvec.getOrigin(), intersect); //Distance entre lumiére ( origine ) et intersection (camera / object )

					if (distance1 + eps <distance2){ //si l'intersection lumiére / objet ce fait avant l'intersection camera / objet

						double fact = 0.2;
						Vector3 color = t.getColor(intersect.x, intersect.y);

						screen.setPixel(i, j, qRgb(color.x*fact, color.y*fact, color.z*fact));//alors pixel d'intersection camera/objet represente l'ombre
						//screen.setPixel(i,j,qRgb(255.,255.,0.));//alors pixel d'intersection camera/objet represente l'ombre
					}
					else{

						/*Diffu v2*/
						Vector3 L = Vector3::normalize(light - intersect);
						Vector3 N = t.normal(intersect);
						double colorDiffuse = L*N;
						colorDiffuse = std::abs(colorDiffuse) / (Constante::pi)* 2 + 0.1;

						Vector3 color = t.getColor(intersect.x, intersect.y);


						screen.setPixel(i, j, qRgb(color.x * colorDiffuse, color.y * colorDiffuse, color.z * colorDiffuse));//sinon represente lumiére 


					}


				}
				else
				{
					screen.setPixel(i, j, qRgb(155, 255, 255)); // aucun contact avec l'objet.
				}
			}
		}

	}

	// renvoi l'image sur laquelle la fct raytrace dessine.
	const QImage& getScreen()
	{
		return screen;
	}
	~Renderer() {};
};

