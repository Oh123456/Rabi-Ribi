#pragma once
#include "Effect.h"
class WizardProjectileEffect : public EffectBoday
{
	SUPER(EffectBoday);
public:
	WizardProjectileEffect();
	~WizardProjectileEffect();

	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;
private:
	void Effect();
private:
	const float exposureEffectValue = 0.8f;
	float exposureValue;
	TimerHandle timerHandle;
};

