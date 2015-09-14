#include "tp1mg2.h"
#include "Terrain.h"
#include "Debug.h"
#include "heightmapwidget.h"
#include "Camera.h"
#include <QtWidgets/QApplication>
#include <qtextedit.h>
#include <ctime>

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
	QImage hm("Resources/testhm");
	Terrain t(hm, 10, 10, 20.0, 20.0);
	QTextEdit logTxt;
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
	for (int i = 0; i < 10; i++)
	{
		Vector3 tmp1((int)(rand() % 180) / 10.0, (int)(rand() % 180) / 10.0, (int)(rand() % 200) / 10.0);
		Vector3 tmp2((int)(rand() % 180) / 10.0, (int)(rand() % 180) / 10.0, (int)(rand() % 200) / 10.0);
		logTxt.append(d.testIntersection(Ray(tmp1, tmp2), t).toHtmlEscaped());
	}
	//logTxt.append(d.printVector3(t.getPoint(90.0, 10.0)));
	logTxt.append(QString('\n').toHtmlEscaped());
	Terrain t2 = Terrain::CreateRidgeFractal(10, 10, 20.0, 20.0, 255.0);
	logTxt.append(d.printTerrain(t2).toHtmlEscaped());
	logTxt.show();

	/*for (int z = 0; z < t.getHeight(); ++z)
	{
	for (int x = 0; x < t.getWidth(); ++x)
	{
	double z = t.getPoint(x, z).z;
	}
	}*/
	Camera c(Vector3(0.0, 10.0, -5.0), Vector3(0.0, 0.0, 0.0), 12.0);
	HeightmapWidget hmw(&t, 0);
	hmw.show();

	return a.exec();
}
