#include "BunnyBand.h"

HRESULT BunnyBand::Init()
{
	Super::Init();
	IMAGEMANAGER->LoadPng(L"bunny_a", L"Chacter/Enemy/bunny_a");
	bunnyBand.imageName = L"bunny_a";
	bunnyBand.atlasInfo.frameSize = { 64.0f,64.0f };
	bunnyBand.atlasInfo.frame = { 0,0 };
	bunnyBand.affineMatrix = Matrix3x2F::Scale({ 1.5f,1.5f }, {32.0f,32.0f});
	bunnyBand.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	return S_OK;
}

void BunnyBand::Update()
{
	Super::Update();
	if (bunnyBand.affineMatrix.m11 > 0.0f)
		bunnyBand.imageLocation = { location.x - 4.0f , location.y};
	else
		bunnyBand.imageLocation = { location.x + 4.0f , location.y};
}
