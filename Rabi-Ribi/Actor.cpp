#include "Actor.h"
#include "GeometryCollision.h"

void Actor::SetCollisionGeometry(const ID2D1PathGeometry * const collisionGeomtry)
{
	this->collisionGeomtry->SetCollision(Cast<ID2D1PathGeometry>(collisionGeomtry),this);
}

void Actor::SetGeomtryLocation(const Location & letfTopLocation, const SIZE_F & size)
{
	this->geomtryLocation.x = letfTopLocation.x + (size.width / 2.0f);
	this->geomtryLocation.y = letfTopLocation.y + (size.height / 2.0f);
}

const ID2D1PathGeometry* Actor::GetCollisionGeomtry()
{
	return this->collisionGeomtry->GetGeometry();
}
