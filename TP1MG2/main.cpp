#include "tp1mg2.h"
#include "Terrain.h"
#include "Debug.h"
#include "Sphere.h"
#include "heightmapwidget.h"
#include "Camera.h"
#include "Renderer.h"
#include <QtWidgets/QApplication>
#include <qtextedit.h>
#include <ctime>
#include<qlabel.h>

// point d'entrée du programme, initialise Qt et les objets necessaire au déroulement du programme
int main(int argc, char *argv[])
{
	srand(time(0));
	QApplication a(argc, argv);
	/*TP1MG2 w;
	w.show(); */
	Debug d;
	QImage hm("Resources/testhm");
	Terrain t(hm); /*Terrain crée grace à une image*/
	Terrain t2 = Terrain::CreateRidgeFractal(1000, 1000, 10.0, 15.0, 255.0); /*Terain créé grace à une fonction*/
	QTextEdit logTxt;
	HeightmapWidget *hmw;
	hmw = new HeightmapWidget(&t2, 0);

	/*Debugage écrie*/
	logTxt.setReadOnly(true);
	//Afficher en écrie le Terrain "t"
	logTxt.insertPlainText(d.printTerrain(t).toHtmlEscaped()); 
	for (int i = 0; i < 10; i++)
	{
		Vector3 tmp(((int)(rand()) % 1800) / 10.0, ((int)(rand()) % 1800) / 10.0, ((int)(rand()) % 2000) / 10.0);
		logTxt.append(d.testInOut(tmp, t).toHtmlEscaped());
	}

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
	
	logTxt.insertPlainText(d.printTerrain(t).toHtmlEscaped());
	logTxt.show();

	// Raytracage de la sphere
	Vector3 origin(1000., 1000., 300.); // Fait office de camera : represente l'emplacement de l'oeil.
	Vector3 light(1000., 1000., 400.);//Fait office de lumiére : represente l'emplacement de la lumiére.
	const int width_scrn = 800;
	const int height_scrn = 600;
	Camera c(origin, Vector3(width_scrn / 2., height_scrn / 2., 0.), 1., Vector3(0., 0., -1.));
	//QImage screen(width_scrn, height_scrn, QImage::Format::Format_RGB32);
	Sphere s(Vector3(0.0, 0., 0.), .5);
	Renderer r(width_scrn, height_scrn, c, light, t2);
	r.Raytrace();

	QLabel l;
	l.setPixmap(QPixmap::fromImage(r.getScreen()));
	l.show();

	
	
	hmw->show();

	return a.exec();
}
