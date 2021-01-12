#pragma once
#include "RotationEffect.h"

class CarrotBombEffect : public RotationEffect
{
	SUPER(RotationEffect);
public:
	CarrotBombEffect();
	~CarrotBombEffect();

	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;

};

