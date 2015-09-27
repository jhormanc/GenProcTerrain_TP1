#include "Camera.h"

Camera::Camera(Vector3 o_, Vector3 a_, double dw, Vector3 up)
{
	o = o_;

	w = Vector3::normalize(a_ - o_);
	u = Vector3::normalize((w ^ up).inv());
	v = w ^ u;

	lu = 16. / 9.;
	lv = 1.;
	lw = dw;
}

Vector3 Camera::PtScreen(int i, int j, int width, int height)
{
	double tu = (double)i / (double)(width - 1);
	double tv = (double)j / (double)(height - 1);

	Vector3 res = o + (w * lw)
		+ u * (-lu * (1 - tu) + tu * lu)
		+ v * (-lv * (1 - tv) + tv * lv);

	return res;
}