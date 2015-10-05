#include "matrix3x3.h"


Matrix3x3::Matrix3x3 ( ) {
	c[9] = { 0 };
}

Matrix3x3::Matrix3x3 ( double coefs[9] ) {
	c[0] = coefs[0]; c[1] = coefs[1]; c[2] = coefs[2];
	c[3] = coefs[3]; c[4] = coefs[4]; c[5] = coefs[5];
	c[6] = coefs[6]; c[7] = coefs[7]; c[8] = coefs[8];
}

Matrix3x3::Matrix3x3 ( const Vector3 & vx, const Vector3 & vy, const Vector3 & vz ) {
	c[0] = vx.x; c[1] = vx.y; c[2] = vx.z;
	c[3] = vy.x; c[4] = vy.y; c[5] = vy.z;
	c[6] = vz.x; c[7] = vz.y; c[8] = vz.z;
}

Matrix3x3 Matrix3x3::operator * ( double k ) const {
	Matrix3x3 A;

	A ( 0, 0 ) = c[0] * k; A ( 0, 1 ) = c[1] * k; A ( 0, 2 ) = c[2] * k;
	A ( 1, 0 ) = c[3] * k; A ( 1, 1 ) = c[4] * k; A ( 1, 2 ) = c[5] * k;
	A ( 2, 0 ) = c[6] * k; A ( 2, 1 ) = c[7] * k; A ( 0, 2 ) = c[8] * k;

	return A;
}

Vector3 Matrix3x3::operator * ( const Vector3 & v ) const {
	double x ( c[0] * v.x + c[1] * v.y + c[2] * v.z );
	double y ( c[3] * v.x + c[4] * v.y + c[5] * v.z );
	double z ( c[6] * v.x + c[7] * v.y + c[8] * v.z );
	return Vector3 ( x, y, z );
}

Matrix3x3 Matrix3x3::transpose ( ) const {
	Matrix3x3 T;
	T ( 0, 0 ) = c[0];	T ( 0, 1 ) = c[3];	T ( 0, 2 ) = c[6];
	T ( 1, 0 ) = c[1];	T ( 1, 1 ) = c[4];	T ( 1, 2 ) = c[7];
	T ( 2, 0 ) = c[2];	T ( 2, 1 ) = c[5];	T ( 2, 2 ) = c[8];
	return T;
}


Matrix3x3::~Matrix3x3 ( ) {
}
