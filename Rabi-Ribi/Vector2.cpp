#include "Vector2.h"

Vector2::Vector2() :
	x(0.0f) , y(0.0f)
{
}

Vector2::Vector2(const Vector2 &  v2) :
	x(v2.x) , y(v2.y)
{
}

Vector2::Vector2(float x, float y) :
	x(x), y(y)
{
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator+(const Vector2& v2)
{
	this->x += v2.x;
	this->y += v2.y;
	return *this;
}

Vector2& Vector2::operator-(const Vector2 & v2)
{
	this->x -= v2.x;
	this->y -= v2.y;
	return *this;
}
