#include "Vector3.h"

// Surcharge des operateurs arithmetiques.

Vector3& Vector3::operator=(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3& Vector3::operator+(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator*(const double x_)
{
	x *= x_;
	y *= x_;
	z *= x_;
	return *this;
}

Vector3& Vector3::operator/(const double x_)
{
	x /= x_;
	y /= x_;
	z /= x_;
	return *this;
}

double Vector3::normalize(const Vector3& v)
{
	return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

// pdt scalaire
Vector3& Vector3::operator*(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
// pdt vectoriel
Vector3& Vector3::operator^(const Vector3& v)
{
	double tmpX = x;
	double tmpY = y;

	x = y*v.z - z*v.y;
	y = z*v.x - tmpX * v.z;
	z = tmpX * v.y - tmpY * v.x;

	return *this;
}
/*
Vector3& Vector3::operator+(int n)
{
x += n;
y += n;
z += n;
return *this;
}
*/
Vector3& Vector3::operator-(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vector3& Vector3::inv()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

