#include "Color.h"


Color::Color()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 1.0f;
}


Color::Color(ColorF& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}

Color& Color::operator=(const ColorF & color)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	return *this;
}
