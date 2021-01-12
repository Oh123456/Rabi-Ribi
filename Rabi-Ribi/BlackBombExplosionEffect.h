#pragma once
#include "ExplosionEffect.h"
class BlackBombExplosionEffect : public ExplosionEffect
{
	SUPER(ExplosionEffect);
public:
	BlackBombExplosionEffect();
	~BlackBombExplosionEffect();

	void Render(ImageInfo& imageInfo) override;
	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;
};

