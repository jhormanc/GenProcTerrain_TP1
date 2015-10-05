#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {

public:
	Vector2 ( ) { x = 0; y = 0; }
	Vector2 ( double u, double v ) { x = u; y = v; }
	~Vector2 ( );

	double x;
	double y;

	Vector2 operator + ( const Vector2 & v ) const { return Vector2 ( x + v.x, y + v.y ); }
	Vector2 operator - ( const Vector2 & v ) const { return Vector2 ( x - v.x, y - v.y ); }
	Vector2 operator * ( double k ) const { return Vector2 ( x * k, y * k ); }
};

#endif
