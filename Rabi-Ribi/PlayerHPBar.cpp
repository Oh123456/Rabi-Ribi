#include "PlayerHPBar.h"

HRESULT PlayerHPBar::Init()
{
	IMAGEMANAGER->LoadPng(L"HPBar",L"HUD/HPBar");
	IMAGEMANAGER->LoadPng(L"hud2_a",L"HUD/hud2_a");
	SIZE_F size = { 67.0f,10.0f };

	sclae = Matrix3x2F::Scale({ 1.5f,1.5f }, { size.width / 2.0f ,size.height / 2.0f });
	hpBarwidth = size.width;
	imageinfo.imageName = L"HPBar";
	imageinfo.atlasInfo.frameSize = size;
	imageinfo.atlasInfo.frame = { 0,0 };
	imageinfo.affineMatrix = sclae * Matrix3x2F::Rotation(90.0f, { size.width / 2.0f ,size.height / 2.0f });
	imageinfo.contrasteInfo.contrast = 1.0f;
	imageinfo.exposureEffectInfo = 2.0f;
	imageinfo.tintColor = { 1.0f,0.0f,1.f,1.0f };
	imageinfo.imageEffect = D2DIE_DEFAULT | D2DIE_CONTRASTEFFECT | D2DIE_TINT | D2DIE_EXPOSUREEFFECT;
	imageinfo.imageLocation = { 50.0f,250.0f };

	HPimageinfo.imageName = L"HPBar";
	HPimageinfo.atlasInfo.frameSize = size;
	HPimageinfo.atlasInfo.frame = { 0,1 };
	HPimageinfo.affineMatrix = sclae * Matrix3x2F::Rotation(90.0f, { size.width / 2.0f ,size.height / 2.0f });
	HPimageinfo.contrasteInfo.contrast = 1.0f;
	HPimageinfo.exposureEffectInfo = 2.0f;
	HPimageinfo.tintColor = { 0.0f,1.0f,0.f,1.0f };
	HPimageinfo.imageEffect = D2DIE_DEFAULT | D2DIE_CONTRASTEFFECT | D2DIE_TINT | D2DIE_EXPOSUREEFFECT;
	HPimageinfo.imageLocation = { 50.0f,250.0f };
	//HPimageinfo

	size = { 135.0f,126.0f };
	erina.imageName = L"hud2_a";
	erina.atlasInfo.frameSize = size;
	erina.atlasInfo.frame = { 0,0 };
	erina.affineMatrix = Matrix3x2F::Scale({0.6f,0.5f}, { size.width/2.0f ,size.height / 2.0f});
	erina.contrasteInfo.contrast = 1.0f;
	erina.imageEffect = D2DIE_DEFAULT | D2DIE_CONTRASTEFFECT;
	erina.imageLocation = { 70.0f,310.0f };
	return S_OK;
}

void PlayerHPBar::Release()
{
}

void PlayerHPBar::Update()
{
	Super::Update();
	HPimageinfo.affineMatrix = sclae * Matrix3x2F::Rotation(270.0f, { HPimageinfo.atlasInfo.frameSize.width / 2.0f ,HPimageinfo.atlasInfo.frameSize.height / 2.0f });
	//HPimageinfo.imageLocation.y = 250.0f + (((67.0f/2.0f) * 1.5f) * (1.0f - hpPersent) * 0.5f);
	HPimageinfo.imageLocation.y = 250.0f + (67.0f - HPimageinfo.atlasInfo.frameSize.width)/ 2.0f;
}

void PlayerHPBar::Render()
{
	Super::Render();
	IMAGEMANAGER->ImageRander(erina);
}
