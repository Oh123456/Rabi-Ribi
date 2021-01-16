#include "FlashingRotationEffect.h"

FlashingRotationEffect::FlashingRotationEffect() : 
	exposureeffect(1.0f) , apha(0.5f) , maxExposureeffect(2.0f) , maxApha(1.0f)
{
	effectframe = EffectFrame::SkyBlue_EllipseProjectlie_Frame;
	anlge = 5.0f;
	TIMERMANAGER->SetTimer(timer,this,&FlashingRotationEffect::Timer, 0.016f);
}

FlashingRotationEffect::~FlashingRotationEffect()
{
}

void FlashingRotationEffect::Update(ImageInfo & imageInfo)
{
	DWORD effectValue = Cast<DWORD>(effectframe);
	imageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	imageInfo.affineMatrix =  Matrix3x2F::Scale({ 1.0f,1.0f }, { imageInfo.atlasInfo.frameSize.width / 2.0f , imageInfo.atlasInfo.frameSize.height / 2.0f }) * 
								Matrix3x2F::Rotation(rotation, { imageInfo.atlasInfo.frameSize.width / 2.0f , imageInfo.atlasInfo.frameSize.height / 2.0f });
	imageInfo.exposureEffectInfo = exposureeffect;
	imageInfo.tintColor = {1.0f,1.0f,1.0f,apha };
	AddImageEffect(imageInfo, D2DIE_TINT);
	AddImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
}

void FlashingRotationEffect::Release(ImageInfo & imageInfo)
{
	TIMERMANAGER->DeleteTimer(timer);
	AddImageEffect(imageInfo, D2DIE_TINT);
	AddImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
}

HRESULT FlashingRotationEffect::SetValue(UINT index, const void * data)
{

	return E_NOTIMPL;
}

void FlashingRotationEffect::Timer()
{
	apha += 0.1f;
	if (apha >= maxApha)
		apha = 0.5f;
	if (exposureeffect >= maxExposureeffect)
		exposureeffect = 1.0f;
	if (effectframe != EffectFrame::Blue_EllipseProjectlie_Frame)
		effectframe = EffectFrame::Blue_EllipseProjectlie_Frame;
	else
		effectframe = EffectFrame::SkyBlue_EllipseProjectlie_Frame;
}
