#pragma once
#include "Enemy.h"
class BunnyBand : public Enemy
{
	SUPER(Enemy)
public:
	BunnyBand() {};
	~BunnyBand() override {};

	HRESULT Init()	override;
	void Update()	override;

	ImageInfo* GetBunnyBandImageInfo_ptr() { return &bunnyBand; }
	void SetSokectLocation(Location location) { sokectLocation = location; }
protected:
	ImageInfo bunnyBand;
	Location sokectLocation;
};

