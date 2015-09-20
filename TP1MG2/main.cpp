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

// point d'entrée du programme, initialise Qt et les objets necessaire au déroulement du programme
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
	QImage hm("Resources/Heightmap");
	Terrain t(hm, 257, 257, 20.0, 20.0); /*Terrain crée grace à une image*/
	Terrain t2 = Terrain::CreateRidgeFractal(100, 100, 10.0, 15.0, 255.0); /*Terain créé grace à une fonction*/
	QTextEdit logTxt;
	HeightmapWidget *hmw;
	hmw = new HeightmapWidget(&t2, 0);

	/*Debugage écrie*/
	logTxt.setReadOnly(true);
	//Afficher en écrie le Terrain "t"
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
	
	//Afficher en écrie le Terrain "t2"
	/*logTxt.append(d.printTerrain(t2).toHtmlEscaped());*/
	
	
	logTxt.show();

	// Raytracage de la sphere
	Vector3 origin(0., 0., -1.); // Fait office de camera : represente l'emplacement de l'oeil.
	Vector3 light(200., 200., -0.7);//Fait office de lumiére : represente l'emplacement de la lumiére.
	const int width_scrn = 800;
	const int height_scrn = 600;
	Camera c(origin, Vector3(0., 0., 0.0), 0.0);
	QImage screen(width_scrn, height_scrn, QImage::Format::Format_RGB32);
	QPixmap pxmp;
	Sphere s(Vector3(0.0, 0.0, 100.0), 93.);
	double f;
	double eps = 0.1;
	double maxFact = - 100000000000.;
	double minFact = 100000000000.;
	for (int i = 0; i < width_scrn; i++)
	{
		for (int j = 0; j < height_scrn; j++)
		{
			Ray r = Ray(origin, Vector3::normalize(c.getPoint(i, j) - origin));
			s.intersection(r, f); //Intersection entre la vue ( camera ) et l'objet.
			//t2.intersection(r, f);
			if (f > noIntersect) //Si intersection
			{
				Vector3 intersect(r.getOrigin()+r.getDirection()*(-f)); //Pour avoir le point d'intersection sur la l'objet ( sphere )
				Vector3 direction = Vector3::normalize(intersect-light); //Pour avoir la direction entre la lumiére ( son origine ) et le point d'intersection sur l'object (sphere )
				Ray lightvec=Ray(light,direction); //On crée le ray.
				
				s.intersection(lightvec,f); //Intersection entre le ray (de la lumiére ) et l'objet ( sphere )

				Vector3 intersectlight(lightvec.getOrigin()+lightvec.getDirection()*(-f)); // coordonée du point d'intersection du Ray sur la sphere.
	/*Je fait un "*(-h)" car je sais pas pourquoi le h retourné est negatif*/	
				intersectlight += lightvec.getDirection() * (eps);// regle l'imprecision des flottants en decalant d'epsilon le point d'intersection vers la lumiere
				double distance1= Vector3::distance(lightvec.getOrigin(),intersectlight); //Distance entre lumiére ( origine ) et intersection (lumiére / object )
				double distance2= Vector3::distance(lightvec.getOrigin(),intersect); //Distance entre lumiére ( origine ) et intersection (camera / object )

				if(distance1<distance2){ //si l'intersection lumiére / objet ce fait avant l'intersection camera / objet
					screen.setPixel(i, j, qRgb(0, 0, 0));//alors pixel d'intersection camera/objet represente l'ombre
				}else{

					// Diffus :
					Vector3 tmpDebug = (intersectlight + direction /* Vector3::normalize(light - intersectlight )*/); // car produit vectorielle est compatible avec la multiplication avec un scalaire.
					Vector3 tmpDebug1 = Vector3::normalize(((intersectlight) ^ tmpDebug) );
					double tmpDebug2 = ((Vector3::normalize(s.normal(intersectlight))) * (tmpDebug1 )) ; // car produit scalaire bilinéaire. 
					/*double fact = ((tmpDebug2));// / pi)  ; // calcul de la force de la lumiere
					fact = ((fact) + 1.) * 0.5; //  0.0 <= fact <= 1.0 pour diminuer la luminosité (valeurs expermientales)
					maxFact = std::max(fact, maxFact);
					minFact = std::min(fact, minFact);
					double color = std::max(0., std::min(fact, 1.));*/
					double fact = 1.;
					screen.setPixel(i, j, qRgb(150 * fact , 255 * fact, 255 * fact));//sinon represente lumiére 
				}
				
			}
			else
			{
				screen.setPixel(i, j, qRgb(255, 255, 255)); // aucun contact avec l'objet.
			}
		}
	}
	
	QLabel l;
	l.setPixmap(QPixmap::fromImage(screen));
	l.show();

	
	
	hmw->show();

	return a.exec();
}
