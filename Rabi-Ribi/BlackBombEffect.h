#pragma once
#include "RotationEffect.h"
class BlackBombEffect : public RotationEffect
{
	SUPER(RotationEffect);
public:
	BlackBombEffect();
	~BlackBombEffect();

	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;

	HRESULT  SetValue(UINT index, const void* data) override { return S_OK; };
};

