#include "Camera.h"

Camera::Camera(Vector3 o_, Vector3 a_, double dw)
{
	o = o_;
	Vector3 tmpw = a_ - o;
	w = Vector3::normalize(tmpw);
	Vector3 tmpu1 = w ^ Vector3(0, 0, 1);
	Vector3 tmpu = (tmpu1).inv();
	u = Vector3::normalize(tmpu);
	v = w^u;

	lu = 400.;
	lv = 300.;
	lw = dw;
}

Vector3 Camera::PtScreen(int i, int j, int width, int height)
{
	double tu = i / (width - 1);
	double tv = j / (height - 1);
	return o + (w * lw)
		+ u * (-lu*(1 - tu) + tu*lu)
		+ v * (-lv*(1 - tv) + tv*lv);

}

Vector3 Camera::getPoint(int i, int j)
{
	double width = lu + lu;
	double height = lv + lv;
	double x = (2 * (i - (width * 0.5)) / width) * (width / height); // -1.0 <= x <= 1.0
	double y = (2 * (j - (height * 0.5)) / height); //  ...  y ...
	return Vector3(x, y, 0);
}