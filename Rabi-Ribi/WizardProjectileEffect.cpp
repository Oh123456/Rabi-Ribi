#include "WizardProjectileEffect.h"

WizardProjectileEffect::WizardProjectileEffect() 
	: exposureValue(exposureEffectValue) 
{
	TIMERMANAGER->SetTimer(timerHandle,this,&WizardProjectileEffect::Effect , 0.016f*5.0f );
	effectframe = EffectFrame::Small_Blue_Frame;
}

WizardProjectileEffect::~WizardProjectileEffect()
{
}

void WizardProjectileEffect::Update(ImageInfo& imageInfo)
{
	DWORD effectValue = Cast<DWORD>(effectframe);
	imageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	AddImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
	AddImageEffect(imageInfo, D2DIE_TINT);
	imageInfo.tintColor = Color::RGBAToVector_4f(RGBAColor({95,95,95,255}));
	imageInfo.exposureEffectInfo = exposureValue;
	if (imageInfo.exposureEffectInfo >= 2.0f)
		exposureValue = -1.0f;
	
}

void WizardProjectileEffect::Release(ImageInfo& imageInfo)
{
	RemoveImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
	RemoveImageEffect(imageInfo, D2DIE_TINT);
	TIMERMANAGER->DeleteTimer(timerHandle);
}

void WizardProjectileEffect::Effect()
{
	exposureValue += exposureEffectValue;
}
