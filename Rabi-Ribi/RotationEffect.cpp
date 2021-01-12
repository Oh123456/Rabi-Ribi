#include "RotationEffect.h"

RotationEffect::RotationEffect() :
	anlge(5.0f) , rotation(0.0f)
{
	TIMERMANAGER->SetTimer(rotationTImer, this, &RotationEffect::RotationTimer, 0.16f);
}

void RotationEffect::RotationTimer()
{
	rotation += anlge;
	if (rotation >= 360.0f)
		rotation -= 360.0f;
}
