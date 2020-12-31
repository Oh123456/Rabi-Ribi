#include "Eenemy.h"

Eenemy::Eenemy()
{
}

Eenemy::~Eenemy()
{
}

void Eenemy::Update()
{
	Super::Update();
	cameraLocation = CAMERA->GetLocation();
	location.x = { worldLocation.x - cameraLocation.x };
	location.y = { worldLocation.y - cameraLocation.y };
	geomtryLocation.x = { worldLocation.x - cameraLocation.x };
	geomtryLocation.y = { worldLocation.y - cameraLocation.y };
}

void Eenemy::MoveCharacter()
{
	location = geomtryLocation;
	worldLocation = { geomtryLocation.x + cameraLocation.x, geomtryLocation.y + cameraLocation.y };
}
