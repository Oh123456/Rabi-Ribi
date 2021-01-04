#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(const Vector2&  v2);
	Vector2(float x ,float y);
	virtual ~Vector2();

	Vector2& operator+(const Vector2& v2);
	Vector2& operator-(const Vector2& v2);

	float x;
	float y;
};
