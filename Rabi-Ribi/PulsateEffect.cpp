#include "PulsateEffect.h"

PulsateEffect::PulsateEffect() :
	size(0.8f), apha(1.0f) , exposureeffect(1.2f)
{
	TIMERMANAGER->SetTimer(timer,this,&PulsateEffect::Timer, 0.2f);
	effectframe = EffectFrame::Blue_Projectlie_Frame;
}

PulsateEffect::~PulsateEffect()
{
}

void PulsateEffect::Update(ImageInfo& imageInfo)
{
	DWORD effectValue = Cast<DWORD>(effectframe);
	imageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	imageInfo.affineMatrix = Matrix3x2F::Rotation(RadianToDegree(*onwerAngle), { imageInfo.atlasInfo.frameSize.width / 2.0f , imageInfo.atlasInfo.frameSize.height / 2.0f })* AFFINEMATRIX_3X2_SCALE(size, { imageInfo.atlasInfo.frameSize.width / 2.0f });
	imageInfo.exposureEffectInfo = exposureeffect;
	AddImageEffect(imageInfo, D2DIE_TINT);
	AddImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
	imageInfo.tintColor = { 1.0f,1.0f,1.0f,apha };
}

void PulsateEffect::Release(ImageInfo& imageInfo)
{
	TIMERMANAGER->DeleteTimer(timer);
	RemoveImageEffect(imageInfo, D2DIE_TINT);
	RemoveImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
}

void PulsateEffect::Timer()
{
	size += 0.1f;
	if (size > 0.9f)
		size = 0.7f;
	apha += 0.1f;
	if (apha >= 1.0f)
		apha = 0.5f;
	exposureeffect += 1.f;
	if (exposureeffect > 1.2f)
		exposureeffect = 0.5f;
}
