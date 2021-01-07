#pragma once
#include "Enemy.h"
class BunnyBand : public Enemy
{
	SUPER(Enemy)
public:
	BunnyBand() {};
	~BunnyBand() override {};

	HRESULT Init()	override;

	ImageInfo* GetBunnyBandImageInfo_ptr() { return &bunnyBand; }
protected:
	ImageInfo bunnyBand;
};

