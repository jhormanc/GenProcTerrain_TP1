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

	double _00, _01, _02;
	double _10, _11, _12;
	double _20, _21, _22;

	Matrix3x3 transpose ( ) const;
};

#endif // MATRIX3x3_H
