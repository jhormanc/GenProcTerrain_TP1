#pragma once
#include "Vector3.h"

class Camera
{
	Vector3 o, u, v, w;
	double lu, lv, lw;
public:
	Camera(Vector3 o_, Vector3 d, double dw);
	Vector3 PtScreen(int i, int j, int width, int height);
	Vector3 getPoint(int i, int j);
};