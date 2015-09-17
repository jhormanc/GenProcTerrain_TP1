#include "Camera.h"

Camera::Camera(Vector3 o_, Vector3 a_, double dw)
{
	o = o_;
	Vector3 tmp2 = (a_ - o);
	w = tmp2 / tmp2.normal();
	Vector3 tmp = (w ^ Vector3(0, 0, 1)).inv();
	u = Vector3::normalize(tmp / tmp.normal()); 
	v = w^u;
	lu = 16.0 / 20.0;
	lv = 9.0 / 20.0;
	lw = 12.0;
}

Vector3 Camera::PtScreen(int i, int j, int width, int height)
{
	double tu = i / (width - 1);
	double tv = j / (height - 1);
	return o + (w * lw)
		+ u * (-lu*(1 - tu) + tu*lu)
		+ v * (-lv*(1 - tv) + tv*lv);

}