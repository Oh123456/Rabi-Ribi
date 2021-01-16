#include "CarrotBombEffect.h"

CarrotBombEffect::CarrotBombEffect()
{
	effectframe = (EffectFrame::Carrot_Bomb_Frame);
}

CarrotBombEffect::~CarrotBombEffect()
{
}

void CarrotBombEffect::Update(ImageInfo & imageInfo)
{
	DWORD effectValue = Cast<DWORD>(effectframe);
	imageInfo.atlasInfo.frameSize = { 31.0f,31.0f };
	imageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	imageInfo.imageEffect = D2DIE_DEFAULT;
	D2D1_POINT_2F  center = { imageInfo.atlasInfo.frameSize.width / 2.0f ,imageInfo.atlasInfo.frameSize.height / 2.0f };
	imageInfo.affineMatrix = Matrix3x2F::Rotation(rotation, center) * Matrix3x2F::Scale({ 0.5f,0.5f }, center);
}

void CarrotBombEffect::Release(ImageInfo & imageInfo)
{
	Super::Release(imageInfo);
	imageInfo.affineMatrix = Matrix3x2F::Identity();
}

HRESULT CarrotBombEffect::SetValue(UINT index, const void * data)
{
	
	return S_OK;
}
