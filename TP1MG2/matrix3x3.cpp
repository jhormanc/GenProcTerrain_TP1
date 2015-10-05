#include "matrix3x3.h"


Matrix3x3::Matrix3x3 ( ) {
	_00 = 0; _01 = 0; _02 = 0;
	_10 = 0; _11 = 0; _12 = 0;
	_20 = 0; _21 = 0; _22 = 0;
}

Matrix3x3::Matrix3x3 ( double coefs[9] ) {
	_00 = coefs[0]; _01 = coefs[1]; _02 = coefs[2];
	_10 = coefs[3]; _11 = coefs[4]; _12 = coefs[5];
	_20 = coefs[6]; _21 = coefs[7]; _22 = coefs[8];
}

Matrix3x3::Matrix3x3 ( const Vector3 & vx, const Vector3 & vy, const Vector3 & vz ) {
	_00 = vx.x; _01 = vx.y; _02 = vx.z;
	_10 = vy.x; _11 = vy.y; _12 = vy.z;
	_20 = vz.x; _21 = vz.y; _22 = vz.z;
}

Matrix3x3 Matrix3x3::operator * ( double k ) const {
	Matrix3x3 A;

	A._00 = _00 * k; A._01 = _01 * k; A._02 = _02 * k;
	A._10 = _10 * k; A._11 = _11 * k; A._12 = _12 * k;
	A._20 = _20 * k; A._21 = _21 * k; A._22 = _22 * k;

	return A;
}

Vector3 Matrix3x3::operator * ( const Vector3 & v ) const {
	double x ( _00 * v.x + _01 * v.y + _02 * v.z );
	double y ( _10 * v.x + _11 * v.y + _12 * v.z );
	double z ( _20 * v.x + _21 * v.y + _22 * v.z );
	return Vector3 ( x, y, z );
}

Matrix3x3 Matrix3x3::transpose ( ) const {
	Matrix3x3 T;
	T._00 = _00;	T._01 = _10;	T._02 = _20;
	T._10 = _01;	T._11 = _11;	T._12 = _21;
	T._20 = _02;	T._21 = _12;	T._22 = _22;
	return T;
}


Matrix3x3::~Matrix3x3 ( ) {
}
