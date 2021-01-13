#include "Vector2F.h"

Vector2_F::Vector2_F() :
	Vector2(0.0f,0.0f)
{
}

Vector2_F::Vector2_F(const Vector2 &  v2) :
	Vector2(v2)
{
}

Vector2_F::Vector2_F(const Location & location) :
	Vector2(location.x , location.y)
{
}

Vector2_F::Vector2_F(float x, float y) :
	Vector2(x, y)
{
}

Vector2_F& Vector2_F::operator+(const Vector2_F & v2)
{
	Cast<Vector2>(this)->x += v2.x;
	Cast<Vector2>(this)->y += v2.y;
	return *this;
}

Vector2_F& Vector2_F::operator-(const Vector2_F & v2)
{
	Cast<Vector2>(this)->x -= v2.x;
	Cast<Vector2>(this)->y -= v2.y;
	return *this;
}

Vector2_F& Vector2_F::operator+(const Location & v2)
{
	this->x += v2.x;
	this->y += v2.y;
	return *this;
}

Vector2_F& Vector2_F::operator-(const Location & v2)
{
	this->x -= v2.x;
	this->y -= v2.y;
	return *this;
}

bool Vector2_F::operator==(const Vector2_F & v2)
{
	if ((this->x == v2.x)&(this->y == v2.y))
		return true;
	return false;
}

bool Vector2_F::operator==(const Location & v2)
{
	if ((this->x == v2.x)&(this->y == v2.y))
		return true;
	return false;
}

Location Vector2_F::ToLocation()
{
	return { x,y };
}
