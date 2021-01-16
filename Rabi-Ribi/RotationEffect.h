#pragma once
#include "Effect.h"
class RotationEffect : public EffectBody
{
public:
	RotationEffect();
	~RotationEffect();

	void Release(ImageInfo& imageInfo) override;
private:
	void RotationTimer();
protected:
	float anlge;
	float rotation;
	TimerHandle rotationTImer;
};

