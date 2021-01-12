#pragma once
#include "Effect.h"
class RotationEffect : public EffectBody
{
public:
	RotationEffect();
private:
	void RotationTimer();
protected:
	float anlge;
	float rotation;
	TimerHandle rotationTImer;
};

