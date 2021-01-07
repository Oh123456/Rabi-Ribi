#pragma once
#include "pch.h"
#include "Volume.h"

struct RGBAColor
{
	LONG r;
	LONG g;
	LONG b;
	LONG a;
};


class Color
{
	typedef Volume ColorValue;
	typedef Volume ColorValue;
public:
	Color();
	Color(ColorF& color);

	Color& operator= (const ColorF& color);

	
	static D2D1_VECTOR_4F RGBAToVector_4f(RGBAColor color);

	ColorF GetColor() { return ColorF(r.c_float(), g.c_float(), b.c_float(), a.c_float()); }
	D2D1_VECTOR_4F GetColor_v4() { return { r.c_float(),g.c_float(),b.c_float(),a.c_float() }; }
	float _GetRValue() { return r.c_float(); }
	float _GetGValue() { return g.c_float(); }
	float _GetBValue() { return b.c_float(); }
	float _GetAValue() { return a.c_float(); }
private:
	ColorValue r;
	ColorValue g;
	ColorValue b;
	ColorValue a;
};

