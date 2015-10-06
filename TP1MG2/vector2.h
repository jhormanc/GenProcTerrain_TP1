#pragma once
#include <cmath>
#include <algorithm>
// classe utilitaire represente les points dans l'espace 2D.
class Vector2 {
public:
	double x, y;

	// Contructeurs
	Vector2(double x_, double y_) :x(x_), y(y_){};
	Vector2(double x_) :x(x_), y(x_){};
	Vector2() :x(0.0), y(0.0){};
	Vector2(const Vector2& v) : x(v.x), y(v.y){};

	inline Vector2 abs() const
	{
		return Vector2(std::abs(x), std::abs(y));
	}

	inline Vector2 max(double x_) const
	{
		return Vector2(std::max(x, x_), std::max(y, x_));
	}

	inline double normal() const
	{
		return std::sqrt(x*x + y*y);
	}

	inline Vector2 operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

	inline Vector2 operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}
};
