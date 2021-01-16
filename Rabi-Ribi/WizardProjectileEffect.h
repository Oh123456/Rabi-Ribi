#pragma once
#include "Effect.h"
class WizardProjectileEffect : public EffectBody
{
	SUPER(EffectBody);
public:
	WizardProjectileEffect();
	~WizardProjectileEffect();

	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;

	HRESULT  SetValue(UINT index, const void* data) override { return S_OK; };
private:
	void Effect();
private:
	const float exposureEffectValue = 0.8f;
	float exposureValue;
	TimerHandle timerHandle;
};

