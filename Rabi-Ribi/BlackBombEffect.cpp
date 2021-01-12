#include "BlackBombEffect.h"

BlackBombEffect::BlackBombEffect()
{
	
}

BlackBombEffect::~BlackBombEffect()
{
}

void BlackBombEffect::Update(ImageInfo& imageInfo)
{
	DWORD effectValue = Cast<DWORD>(EffectFrame::Small_Blue_Frame);
	imageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	imageInfo.affineMatrix = Matrix3x2F::Rotation(rotation, {imageInfo.atlasInfo.frameSize.width / 2 ,imageInfo.atlasInfo.frameSize.height / 2 });
}

void BlackBombEffect::Release(ImageInfo& imageInfo)
{
	imageInfo.affineMatrix = Matrix3x2F::Identity();
	TIMERMANAGER->DeleteTimer(rotationTImer);
}
