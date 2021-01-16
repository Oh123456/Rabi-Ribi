#pragma once
#include "Effect.h"
class GradationEffect : public EffectBody
{
	SUPER(EffectBody);
public:
	GradationEffect();
	~GradationEffect();

	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;

	void SetonwerAngle(const float* value) { onwerAngle = value; };
	HRESULT  SetValue(UINT index, const void* data) override;
private:
	void Timer();
private:
	TimerHandle timer;
	D2D1_VECTOR_4F tintValue;
	float exposureeffect;
	float maxExposureeffect;
	float apha;
	float maxApha;
	const float* onwerAngle;
};

