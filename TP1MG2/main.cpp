#include "tp1mg2.h"
#include "Terrain.h"
#include "Debug.h"
#include "Sphere.h"
#include "heightmapwidget.h"
#include "Camera.h"
#include <QtWidgets/QApplication>
#include <qtextedit.h>
#include <ctime>
#include<qlabel.h>

// point d'entr�e du programme, initialise Qt et les objets necessaire au d�roulement du programme
// Vector2 pour point (utile dans raymarch)
// test raymarching
// Terrain : static Terrain CreateRidgeFractal();
int main(int argc, char *argv[])
{
	srand(time(0));
	QApplication a(argc, argv);
	/*TP1MG2 w;
	w.show(); */
	Debug d;
	QImage hm("Resources/testhm");
	Terrain t(hm, 257, 257, 0.1, 0.1); /*Terrain cr�e grace � une image*/
	Terrain t2 = Terrain::CreateRidgeFractal(1000, 1000, 10.0, 15.0, 255.0); /*Terain cr�� grace � une fonction*/
	QTextEdit logTxt;
	HeightmapWidget *hmw;
	hmw = new HeightmapWidget(&t2, 0);

	/*Debugage �crie*/
	logTxt.setReadOnly(true);
	//Afficher en �crie le Terrain "t"
	/*logTxt.insertPlainText(d.printTerrain(t).toHtmlEscaped()); 
	for (int i = 0; i < 10; i++)
	{
		Vector3 tmp(((int)(rand()) % 1800) / 10.0, ((int)(rand()) % 1800) / 10.0, ((int)(rand()) % 2000) / 10.0);
		logTxt.append(d.testInOut(tmp, t).toHtmlEscaped());
	}*/

	logTxt.append(d.printVector3(t.getPoint(90.0, 10.0)).toHtmlEscaped());
	logTxt.append(d.testIntersection(Ray(Vector3(0.0, 0.0, 10.0), Vector3(1.0, 1.0, -5.0)), t).toHtmlEscaped());
	logTxt.append(d.testIntersection(Ray(Vector3(0.0, 0.0, 10.0), Vector3(1.0, 1.0, 5.0)), t).toHtmlEscaped());
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 255), Vector3(1.0, 1.0, -100.0)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(1.0, 1.0, 5.0)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(2.0, 1.0, -20)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(0.5, 1.5, -20)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(0.0, 0.5, 5)));
	//hmw->AddRay(Ray(Vector3(0.0, 0.0, 100.0), Vector3(1.0, 1.0, 50)));

	for (int i = 0; i < 10; i++)
	{
		Vector3 tmp1((int)(rand() % 180) / 10.0, (int)(rand() % 180) / 10.0, (int)(rand() % 200) / 10.0 + 5);
		Vector3 tmp2((int)(rand() % 180) / 10.0, (int)(rand() % 180) / 10.0, (int)(rand() % 200) / 10.0 + 5);
		logTxt.append(d.testIntersection(Ray(tmp1, tmp2), t).toHtmlEscaped());
	}
	//logTxt.append(d.printVector3(t.getPoint(90.0, 10.0)));
	logTxt.append(QString('\n').toHtmlEscaped());
	
	//Afficher en �crie le Terrain "t2"
	/*logTxt.append(d.printTerrain(t2).toHtmlEscaped());*/
	
	logTxt.insertPlainText(d.printTerrain(t).toHtmlEscaped());
	logTxt.show();

	// Raytracage de la sphere
	Vector3 origin(0., .0
		, 3.0); // Fait office de camera : represente l'emplacement de l'oeil.
	Vector3 light(-1., 2.
		, 3.0);//Fait office de lumi�re : represente l'emplacement de la lumi�re.
	const int width_scrn = 800;
	const int height_scrn = 600;
	Camera c(origin, Vector3(0., 0., .0), 1.);
	QImage screen(width_scrn, height_scrn, QImage::Format::Format_RGB32);
	Sphere s(Vector3(0.0, 0., 0.), .5);
	double f;
	double eps = 0.1;
	double maxFact = - 100000000000.;
	double minFact = 100000000000.;
	for (int i = 0; i < width_scrn; i++)
	{
		for (int j = 0; j < height_scrn; j++)
		{
			Ray r = Ray(origin, Vector3::normalize(c.PtScreen(i, j, width_scrn, height_scrn) - origin));
			
			t.intersection(r, f); //Intersection entre la vue ( camera ) et l'objet.
			//t2.intersection(r, f);
			if (f > noIntersect) //Si intersection
			{
				Vector3 intersect(r.getOrigin()+r.getDirection()*(abs(f))); //Pour avoir le point d'intersection sur la l'objet ( sphere )
				Vector3 direction = Vector3::normalize(intersect-light); //Pour avoir la direction entre la lumi�re ( son origine ) et le point d'intersection sur l'object (sphere )
				Ray lightvec=Ray(light,direction); //On cr�e le ray.
				
				t.intersection(lightvec,f); //Intersection entre le ray (de la lumi�re ) et l'objet ( sphere )

				Vector3 intersectlight(lightvec.getOrigin()+lightvec.getDirection()*(abs(f))); // coordon�e du point d'intersection du Ray sur la sphere.
	/*Je fait un "*(-h)" car je sais pas pourquoi le h retourn� est negatif*/	
				intersectlight += lightvec.getDirection() * (eps);// regle l'imprecision des flottants en decalant d'epsilon le point d'intersection vers la lumiere
				double distance1= Vector3::distance(lightvec.getOrigin(),intersectlight); //Distance entre lumi�re ( origine ) et intersection (lumi�re / object )
				double distance2= Vector3::distance(lightvec.getOrigin(),intersect); //Distance entre lumi�re ( origine ) et intersection (camera / object )

				if(distance1<distance2){ //si l'intersection lumi�re / objet ce fait avant l'intersection camera / objet
					screen.setPixel(i, j, qRgb(0, 0, 0));//alors pixel d'intersection camera/objet represente l'ombre
				}else{

					// Diffus :
				
					Vector3 l(Vector3::normalize(light - (intersect)));
					double fact = s.normal(intersect)* l;
					maxFact = std::max(fact, maxFact);
					minFact = std::min(fact, minFact);
					fact = (fact + 1.) * 1.; //  0.0 <= fact <= 1.0 pour diminuer la luminosit� (valeurs expermientales)
					
					double color = std::max(0., std::min(fact, 1.));
				//	double fact = 1.;
					screen.setPixel(i, j, qRgb(255 * color , 255 * color, 255 * color));//sinon represente lumi�re 

				}
				

			}
			else
			{
				screen.setPixel(i, j, qRgb(155, 255, 255)); // aucun contact avec l'objet.
			}
		}
	}
	

	QLabel l;
	l.setPixmap(QPixmap::fromImage(screen));
	l.show();

	
	
//	hmw->show();

	return a.exec();
}
