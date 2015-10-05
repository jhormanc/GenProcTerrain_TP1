#include "../Terrain/Terrain.h"
#include "../Terrain/TerrainHeightmap.h"
#include "../Terrain/TerrainFractal.h"
#include "Debug.h"
#include "heightmapwidget.h"
#include "Camera.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererConfig1.h"
#include "../Renderer/RendererConfig2.h"
#include "../Renderer/RendererConfig3.h"
#include "../Renderer/RendererConfig4.h"
#include "../Renderer/RendererSphere.h"
#include "../Renderer/RendererOpUnaire.h"
#include "../Renderer/RendererCube.h"
#include "../Renderer/RendererBox.h"

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
//	Debug d;
	Terrain * t2 = new TerrainFractal(1000, 1000); // Terain créé grace à une fonction
//	QTextEdit * logTxt = new QTextEdit();
	QLabel l;
	//HeightmapWidget * hmw = new HeightmapWidget(t2, 0);

	//t2->GetMesh()->save("C:/Users/jhormanc/Desktop/test", 10);

	//Renderer * r = new RendererOpUnaire();
	Renderer * r = new RendererSphere();
	//m.execMesure();

	// DEBUG
//	d.execTest(logTxt);
//	logTxt->show();

	// Raytracage du terrain
	r->Raytrace();
	l.setPixmap(QPixmap::fromImage(r->getScreen()));
	l.show();

	
    //hmw->show();

	delete t2;
	
	a.exec();
//	delete logTxt;
	//delete hmw;
	delete r;
	return 0;
	
}
