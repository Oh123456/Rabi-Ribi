#include "GradationEffect.h"

GradationEffect::GradationEffect() :
	maxApha(0.5f), maxExposureeffect(2.0f), apha(0.2f) , exposureeffect(2.0f) , onwerAngle(nullptr),
	tintValue({0.2f,0.2f,0.0f,0.8f})
{
	effectframe = EffectFrame::Red_Projectlie_Frame;
	TIMERMANAGER->SetTimer(timer, this, &GradationEffect::Timer, 0.2f);
}

GradationEffect::~GradationEffect()
{
	
}

void GradationEffect::Update(ImageInfo & imageInfo)
{
	DWORD effectValue = Cast<DWORD>(effectframe);
	imageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	imageInfo.affineMatrix = Matrix3x2F::Rotation(RadianToDegree(*onwerAngle), { imageInfo.atlasInfo.frameSize.width / 2.0f , imageInfo.atlasInfo.frameSize.height / 2.0f }) *
		Matrix3x2F::Scale({ 0.7f,0.5f }, { imageInfo.atlasInfo.frameSize.width / 2.0f , imageInfo.atlasInfo.frameSize.height / 2.0f });
	imageInfo.exposureEffectInfo = exposureeffect;
	imageInfo.tintColor = tintValue;
	AddImageEffect(imageInfo, D2DIE_TINT);
	AddImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
}

void GradationEffect::Release(ImageInfo & imageInfo)
{
	TIMERMANAGER->DeleteTimer(timer);
	AddImageEffect(imageInfo, D2DIE_TINT);
	AddImageEffect(imageInfo, D2DIE_EXPOSUREEFFECT);
}

HRESULT GradationEffect::SetValue(UINT index, const void * data)
{
	void* lpdata = const_cast<void *>(data);
	switch (index)
	{
	case static_cast<UINT>(GADATIONEFFECT::ONWER_ANLGE):
		onwerAngle = nullptr;
		onwerAngle = static_cast<float*>(lpdata);
		return S_OK;
		break;
	case static_cast<UINT>(GADATIONEFFECT::TINT_VALUE):
		tintValue = *(static_cast<D2D1_VECTOR_4F*>(lpdata));
		return S_OK;
		break;
	case static_cast<UINT>(GADATIONEFFECT::Max_Exposureeffect):
	{
		maxExposureeffect = *(static_cast<float*>(lpdata));
		return S_OK;
	}
	case static_cast<UINT>(GADATIONEFFECT::MAX_APHA):
		maxApha = *(static_cast<float*>(lpdata));
		return S_OK;
	break;
	default:
		break;
	}
	return E_NOTIMPL;
}

void GradationEffect::Timer()
{

	apha += 0.1f;
	if (apha >= maxApha)
		apha = 0.3f;
	tintValue = { 1.0f,0.8f,0.2f + apha,0.0f };
	tintValue.w = apha;
}
