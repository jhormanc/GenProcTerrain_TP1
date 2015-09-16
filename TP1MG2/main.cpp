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
	Terrain t(hm, 257, 257, 20.0, 20.0);
	Terrain t2 = Terrain::CreateRidgeFractal(100, 100, 10.0, 15.0, 255.0);
	QTextEdit logTxt;
	HeightmapWidget *hmw;
	hmw = new HeightmapWidget(&t2, 0);

	logTxt.setReadOnly(true);
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
	
	logTxt.append(d.printTerrain(t2).toHtmlEscaped());
	logTxt.show();

	// Raytracage de la sphere
	Vector3 origin(0.0, 0.0, -1.0); // Fait office de camera : represente l'emplacement de l'oeil.
	//Camera c(origin, Vector3(0.0, 0.0, 0.0), 12.0);
	const int width_scrn = 800;
	const int height_scrn = 600;
	QImage screen(width_scrn, height_scrn, QImage::Format::Format_RGB32);
	QPixmap pxmp;
	Vector3 intersect;
	Sphere s(Vector3(0.0, 0.0, 0.0), 0.8);
	for (int i = 0; i < width_scrn; i++)
	{
		for (int j = 0; j < height_scrn; j++)
		{
			double x = 2 * (i - (width_scrn * 0.5)) / width_scrn; // -1.0 <= x <= 1.0
			double y = 2 * (j - (height_scrn * 0.5)) / height_scrn; //  ...  y ...
			if ((intersect = s.intersection(Ray(origin, Vector3::normalize(Vector3(x, y, 0) - origin)))) != Vector3(-10, -10, -10))
			{
				screen.setPixel(i, j, qRgb(255, 255, 255));
			}
			else
			{
				screen.setPixel(i, j, qRgb(0, 0, 0));
			}
		}
	}

	QLabel l;
	l.setPixmap(QPixmap::fromImage(screen));
	l.show();

	
	
	hmw->show();

	return a.exec();
}
