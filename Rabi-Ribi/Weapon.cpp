#include "Weapon.h"

Weapon::Weapon()
{
	 IgnoreTerrain = true; 
	 actorType =  ActorType::Weapone;
}

Weapon::~Weapon()
{
}

void Weapon::Update()
{
	Super::Update();
	this->MoveMent();
	this->MoveEnd(worldLocation);
}

void Weapon::MoveMent()
{

}

void Weapon::MoveEnd(Location& worldLocation)
{
	worldLocation = { location.x + cameraLocation.x, location.y + cameraLocation.y };
	imageInfo.imageLocation = location;
}
