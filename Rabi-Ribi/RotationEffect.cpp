#include "RotationEffect.h"

RotationEffect::RotationEffect() :
	anlge(0.50f) , rotation(0.0f)
{
	TIMERMANAGER->SetTimer(rotationTImer, this, &RotationEffect::RotationTimer, 0.016f);
}

RotationEffect::~RotationEffect()
{

}

void RotationEffect::Release(ImageInfo & imageInfo)
{
	TIMERMANAGER->DeleteTimer(rotationTImer);
}

void RotationEffect::RotationTimer()
{
	rotation += anlge;
	if (rotation >= 360.0f)
		rotation -= 360.0f;
}
