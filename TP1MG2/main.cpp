//#include "tp1mg2.h"
#include "../Terrain/Terrain.h"
#include "../Terrain/TerrainHeightmap.h"
#include "../Terrain/TerrainFractal.h"
#include "Debug.h"
#include "Sphere.h"
#include "heightmapwidget.h"
#include "Camera.h"
#include "Renderer.h"
#include "RendererConfig1.h"
#include <QtWidgets/QApplication>
#include <qtextedit.h>
#include <ctime>
#include<qlabel.h>

// point d'entrée du programme, initialise Qt et les objets necessaire au déroulement du programme
int main(int argc, char *argv[])
{
	srand(time(0));
	QApplication a(argc, argv);
	Debug d;
	Terrain * t2 = new TerrainFractal(1000, 1000, 10.0, 15.0, 255.0); /*Terain créé grace à une fonction*/
	QTextEdit * logTxt = new QTextEdit();
	QLabel l;
	HeightmapWidget * hmw = new HeightmapWidget(t2, 0);
	Renderer * r = new RendererConfig1();

	/*Debugage écrie*/
	d.execTest(logTxt);
	logTxt->show();

	// Raytracage du terrain
	
	r->Raytrace();
	l.setPixmap(QPixmap::fromImage(r->getScreen()));
	l.show();

	
    hmw->show();

	delete t2;
	
	a.exec();
	delete logTxt;
	delete hmw;
	delete r;
	return 0;
	
}
