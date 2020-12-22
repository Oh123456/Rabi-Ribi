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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	return *this;
}
