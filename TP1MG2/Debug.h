#pragma once

#include<iostream>

#include"Terrain.h"
#include "Vector3.h"
// Classe servant au debug et au test.
class Debug {
public :
	Debug(){};
	// Renvoi une QString du Vector3 v pour l'afficher dans le log (ici QTextEdit).
	QString printVector3(Vector3 v) const;
	// Renvoi une QString du Terrain t pour l'afficher dans le log (ici QTextEdit).
	QString printTerrain(Terrain t) const;
	// Renvoi une QString du resultat de la "collision" entre le point p et le terrain t pour l'afficher dans le log (ici QTextEdit).
	QString testInOut(Vector3 p, Terrain t) const;
	// Renvoi une QString du resultat de la "collision" entre le rayon r et le terrain t pour l'afficher dans le log (ici QTextEdit).
	QString testIntersection(Ray r, Terrain t) const;
	
};