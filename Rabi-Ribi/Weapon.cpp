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
	MoveMent();
	MoveEnd();

}

void Weapon::MoveMent()
{

}

void Weapon::MoveEnd()
{
	worldLocation = { location.x + cameraLocation.x, location.y + cameraLocation.y };
	imageInfo.imageLocation = location;
}
