#include "CarrotBombEffect.h"

CarrotBombEffect::CarrotBombEffect()
{
}

CarrotBombEffect::~CarrotBombEffect()
{
}

void CarrotBombEffect::Update(ImageInfo & imageInfo)
{
	DWORD effectValue = Cast<DWORD>(EffectFrame::Carrot_Bomb_Frame);
	imageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	D2D1_POINT_2F  center = { imageInfo.atlasInfo.frameSize.width / 2.0f ,imageInfo.atlasInfo.frameSize.height / 2.0f };
	imageInfo.affineMatrix = Matrix3x2F::Rotation(rotation, center) * Matrix3x2F::Scale({ 0.5f,0.5f }, center);
}

void CarrotBombEffect::Release(ImageInfo & imageInfo)
{
	imageInfo.affineMatrix = Matrix3x2F::Identity();
}
