#include "PulsateEffect.h"

PulsateEffect::PulsateEffect() :
	size(0.8f), apha(1.0f) , exposureeffect(1.2f) , maxSize(0.9f) , maxApha(1.0f) , maxExposureeffect(1.2f)
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

HRESULT PulsateEffect::SetValue(UINT index, const void * data)
{
	void* lpdata = const_cast<void*>(data);
	switch (index)
	{
	case static_cast<UINT>(PULSATEEFFECT::MAX_SIZE):
	{
		float* value = static_cast<float*>(lpdata);
		if (Range_Included(0.0f, *value, 2.0f))
		{
			maxSize = *value;
			return S_OK;
		}
	}
		break;
	case static_cast<UINT>(PULSATEEFFECT::MAX_APHA):
	{
		float* value = static_cast<float*>(lpdata);
		if (Range_Included(0.0f, *value, 1.0f))
		{
			maxApha = *value;
			return S_OK;
		}
		break;
	}
	case static_cast<UINT>(PULSATEEFFECT::Max_Exposureeffect):
	{	float* value = static_cast<float*>(lpdata);
	if (Range_Included(-2.0f, *value, 2.0f))
	{
		maxExposureeffect = *value;
		return S_OK;
	}
	break;
	}
	default:
		break;
	}
	return S_FALSE;
}

void PulsateEffect::Timer()
{
	size += 0.1f;
	if (size > maxSize)
		size = 0.7f;
	apha += 0.1f;
	if (apha >= maxApha)
		apha = 0.5f;
	exposureeffect += 1.f;
	if (exposureeffect > maxExposureeffect)
		exposureeffect = 0.5f;
}
