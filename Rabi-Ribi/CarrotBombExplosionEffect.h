#pragma once
#include "ExplosionEffect.h"
class CarrotBombExplosionEffect : public ExplosionEffect
{
	SUPER(ExplosionEffect);
public:
	CarrotBombExplosionEffect();
	~CarrotBombExplosionEffect();

	void Render(ImageInfo& imageInfo) override;
	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;

	HRESULT  SetValue(UINT index, const void* data) override { return S_OK; };
};

