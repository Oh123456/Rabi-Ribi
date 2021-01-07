#include "BunnyBand.h"

HRESULT BunnyBand::Init()
{
	Super::Init();
	IMAGEMANAGER->LoadPng(L"bunny_a", L"Chacter/Enemy/bunny_a");
	bunnyBand.imageName = L"bunny_a";
	bunnyBand.atlasInfo.frameSize = { 64.0f,64.0f };
	bunnyBand.atlasInfo.frame = { 0,0 };
	bunnyBand.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	return S_OK;
}
