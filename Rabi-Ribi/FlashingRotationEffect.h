#pragma once
#include "RotationEffect.h"
class FlashingRotationEffect : public RotationEffect
{
	SUPER(RotationEffect);
public:
	FlashingRotationEffect();
	~FlashingRotationEffect();

	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;

	HRESULT  SetValue(UINT index, const void* data) override;
private:
	void Timer();
private:
	TimerHandle timer;
	float exposureeffect;
	float apha;
	float maxExposureeffect;
	float maxApha;
};

