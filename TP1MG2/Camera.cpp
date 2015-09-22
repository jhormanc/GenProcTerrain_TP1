#include "Camera.h"

Camera::Camera(Vector3 o_, Vector3 a_, double dw)
{
	o = o_;
	Vector3 tmpw = a_ - o;
	w = Vector3::normalize(tmpw);
	Vector3 tmpu1 = w ^ Vector3(0, 1, 0);
	Vector3 tmpu = (tmpu1).inv();
	u = Vector3::normalize(tmpu);
	v = w^u;

//	lu = 16./9.;
//	lv = 1.;
	lu = 4./3.;
	lv = 1.;
	lw = dw;
}

Vector3 Camera::PtScreen(int i, int j, int width, int height)
{
	double tu = (double)i / (double)(width - 1);
	double tv = (double)j / (double)(height - 1);
	Vector3 res =  o + (w * lw)
		+ u * (-lu*(1 - tu) + tu*lu)
		+ v * (-lv*(1 - tv) + tv*lv);
	return res;
}

Vector3 Camera::getPoint(int i, int j)
{
	double width = 800;
	double height = 600;
	double x = (2 * (i - (width * 0.5)) / width) * (width / height); // -1.0 <= x <= 1.0
	double y = (2 * ((height * 0.5) - j) / height); //  ...  y ...
	return Vector3(x, y, 0);
}