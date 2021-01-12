#pragma once
#include "Effect.h"
class ExplosionEffect : public EffectBody
{
	SUPER(EffectBody);
public:
	ExplosionEffect();
	~ExplosionEffect();

	void Render(ImageInfo& imageInfo) override;
	void Update(ImageInfo& imageInfo) override;
	void Release(ImageInfo& imageInfo) override;

	bool GetIsEnd() { return isEnd; }
private:
	void CreateExplosionImage();
protected:
	ImageInfo ownerImageInfo;
	deque<ImageInfo> explosionEffctImage;
	TimerHandle explosionTimer;
	int count;
protected:
	bool isEnd;
private:
	bool isOneTime;
	float createExplosinTime;
};

