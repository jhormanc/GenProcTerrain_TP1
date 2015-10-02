#include "../Terrain/Terrain.h"
#include "../Terrain/TerrainHeightmap.h"
#include "../Terrain/TerrainFractal.h"
#include "Debug.h"
#include "Sphere.h"
#include "heightmapwidget.h"
#include "Camera.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererConfig1.h"
#include "../Renderer/RendererConfig2.h"
#include "../Renderer/RendererConfig3.h"
#include "../Renderer/RendererConfig4.h"
#include "../Renderer/RendererConfig5.h"
#include "Mesure.h"

#include <QtWidgets/QApplication>
#include <qtextedit.h>
#include <ctime>
#include<qlabel.h>

// Point d'entrée du programme, initialise Qt et les objets necessaire au déroulement du programme
int main(int argc, char *argv[])
{
	srand(time(0));
	QApplication a(argc, argv);
	QLabel l;
	QTextEdit * logTxt = new QTextEdit();

	// OPENGL
	//Terrain * t2 = new TerrainFractal(1000, 1000); // Terain créé grace à une fonction
	//HeightmapWidget * hmw = new HeightmapWidget(t2, 0);
	//hmw->show();
	//delete t2;

	// DEBUG
	//Debug d;
	/*d.execTest(logTxt);
	logTxt->show();*/

	// Mesures
	//Mesure m;
	//m.execMesure();
	
	// Choix de la configuration à afficher (de RendererConfig1 à RendererConfig5)
	// Changer les couleurs dans Terrain.getColor()
	Renderer * r = new RendererConfig5();

	// Raytracage du terrain
	r->Raytrace();
	l.setPixmap(QPixmap::fromImage(r->getScreen()));
	l.show();
	
	a.exec();
	delete logTxt;
	//delete hmw;
	delete r;
	return 0;
	
}
