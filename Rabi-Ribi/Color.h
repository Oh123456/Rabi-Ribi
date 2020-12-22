#pragma once
#include "pch.h"
class Color
{
public:
	Color();
	Color(ColorF& color);

	Color& operator= (const ColorF& color);

	ColorF GetColor() { return ColorF(r, g, b, a); }
	float _GetRValue() { return r; }
	float _GetGValue() { return g; }
	float _GetBValue() { return b; }
	float _GetAValue() { return a; }
private:
	float r;
	float g;
	float b;
	float a;
};

