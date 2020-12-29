#include "Character.h"
#include "PlayerInput.h"

void Character::MoveGeomtry(Location a)
{
	geomtryLocation = a;
}

void Character::MoveCharacter()
{
	location = geomtryLocation;
}

void Character::MoveCancel(bool isSide, bool isUp)
{
	if (isSide)
		geomtryLocation.x = location.x;
	if (isUp)
		geomtryLocation.y = location.y;
	if (isFalling)
		geomtryLocation.y += acceleration;
	MoveCharacter();
}

void Character::MoveToNewGeomtryLocation(const Location & newLocation)
{
	SetGeomtryLocation(newLocation,this->size);
}

void Character::PlayerInputSetting(PlayerInput* playerInput)
{
}
