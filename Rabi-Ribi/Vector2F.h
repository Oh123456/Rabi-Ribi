#pragma once
#include "Vector2.h"
#include "pch.h"

class Vector2_F : public Vector2
{
public:
	Vector2_F();
	Vector2_F(const Vector2&  v2);
	Vector2_F(const Location& location);
	Vector2_F(float x, float y);

	Vector2_F& operator+(const Vector2_F& v2);
	Vector2_F& operator-(const Vector2_F& v2);
	Vector2_F& operator+(const Location& v2);
	Vector2_F& operator-(const Location& v2);
	bool operator==(const Vector2_F& v2);
	bool operator==(const Location& v2);

	Location ToLocation();
};

