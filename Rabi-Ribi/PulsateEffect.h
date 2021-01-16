#pragma once
#include "Effect.h"
class PulsateEffect : public EffectBody
{
	SUPER(EffectBody);
public:
	PulsateEffect();
	~PulsateEffect();

	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;

	void SetonwerAngle(const float* value) { onwerAngle = value; };
	HRESULT  SetValue(UINT index, const void* data) override;
private:
	void Timer();
private:
	TimerHandle timer;
	float size;
	float apha;
	float exposureeffect;
	float maxSize;
	float maxApha;
	float maxExposureeffect;
	const float* onwerAngle;
};

