#include "Actor.h"

void Actor::SetGeomtryLocation(const Location & letfTopLocation, const SIZE_F & size)
{
	this->geomtryLocation.x = letfTopLocation.x + (size.width / 2.0f);
	this->geomtryLocation.y = letfTopLocation.y + (size.height / 2.0f);
}
