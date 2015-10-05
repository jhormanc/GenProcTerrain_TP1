#ifndef MATRIX3x3_H
#define MATRIX3x3_H

#include "vector3.h"

class Matrix3x3 {

public:
	Matrix3x3 ( );
	Matrix3x3 ( double coefs[9] );
	Matrix3x3 ( const Vector3 & vx, const Vector3 & vy, const Vector3 & vz );
	~Matrix3x3 ( );

	Matrix3x3 operator * ( double k ) const;
	Vector3 operator * ( const Vector3 & v ) const;
	double operator ( ) ( int i, int j ) const { return c[i * 3 + j]; }
	double & operator ( ) ( int i, int j ) { return c[i * 3 + j]; }

	Matrix3x3 transpose ( ) const;

private:
	double c[9];
};

#endif // MATRIX3x3_H
