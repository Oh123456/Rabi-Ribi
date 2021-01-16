#include "BossHPBar.h"

HRESULT BossHPBar::Init()
{
	IMAGEMANAGER->LoadPng(L"BossHP", L"HUD/BossHP");
	IMAGEMANAGER->LoadPng(L"sdcute_a", L"HUD/sdcute_a");
	SIZE_F size = { 496.0f,29.0f };

	sclae = Matrix3x2F::Scale({ 0.7f,0.7f }, { size.width / 2.0f ,size.height / 2.0f });
	hpBarwidth = size.width;
	imageinfo.imageName = L"BossHP";
	imageinfo.atlasInfo.frameSize = size;
	imageinfo.atlasInfo.frame = { 0,0 };
	imageinfo.affineMatrix = sclae;
	imageinfo.contrasteInfo.contrast = 1.0f;
	imageinfo.exposureEffectInfo = 1.5f;
	imageinfo.tintColor = { 1.0f,1.0f,0.5f,1.0f };
	imageinfo.imageEffect = D2DIE_DEFAULT | D2DIE_CONTRASTEFFECT | D2DIE_TINT | D2DIE_EXPOSUREEFFECT;
	imageinfo.imageLocation = { 425.0f,320.0f };

	HPimageinfo.imageName = L"BossHP";
	HPimageinfo.atlasInfo.frameSize = size;
	HPimageinfo.atlasInfo.frame = { 0,1 };
	HPimageinfo.affineMatrix = sclae;
	HPimageinfo.contrasteInfo.contrast = 1.0f;
	HPimageinfo.exposureEffectInfo = 1.0f;
	HPimageinfo.tintColor = { 1.0f,1.5f,0.5f,1.0f };
	HPimageinfo.imageEffect = D2DIE_DEFAULT | D2DIE_CONTRASTEFFECT | D2DIE_TINT | D2DIE_EXPOSUREEFFECT;
	HPimageinfo.imageLocation = { 425.0f,320.0f };

	pace.imageName = L"sdcute_a";
	pace.atlasInfo.frameSize = { 250.0f,250.0f };
	pace.atlasInfo.frame = { 4,1 };
	pace.exposureEffectInfo = 1.0f;
	pace.contrasteInfo.contrast = 1.0f;
	pace.affineMatrix = AFFINEMATRIX_3X2_SCALE(0.25f, 125.0f);
	pace.imageEffect = D2DIE_DEFAULT | D2DIE_CONTRASTEFFECT ;
	pace.imageLocation = { 600.0f,305.0f };


	return S_OK;
}

void BossHPBar::Release()
{
}

void BossHPBar::Update()
{
	Super::Update();
	HPimageinfo.imageLocation.x = 425.0f + (((496.0f) - HPimageinfo.atlasInfo.frameSize.width) / 5.0f) ;
}

void BossHPBar::Render()
{
	Super::Render();
	IMAGEMANAGER->ImageRander(pace);
}
