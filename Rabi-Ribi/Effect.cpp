#include "Effect.h"
#include "WizardProjectileEffect.h"
#include "CarrotBombEffect.h"
#include "CarrotBombExplosionEffect.h"
#include "BlackBombEffect.h"
#include "BlackBombExplosionEffect.h"
#include "PulsateEffect.h"
#include "D2DGraphic.h"

void Effect::SetEffect(EffectKinds effectKinds)
{
	imageInfo.imageLocation = { -10.f,-10.0f };
	switch (effectKinds)
	{
	case EffectKinds::Small_Blue_Effect:
		SAFE_RELEASE(body,imageInfo);
		body = new WizardProjectileEffect;
		break;
	case EffectKinds::Carrot_Bomb:
		SAFE_RELEASE(body, imageInfo);
		body = new CarrotBombEffect;
		break;
	case EffectKinds::Carrot_Bomb_Explosion:
		SAFE_RELEASE(body, imageInfo);
		body = new CarrotBombExplosionEffect;
		break;
	case EffectKinds::Black_Bomb:
		SAFE_RELEASE(body, imageInfo);
		body = new BlackBombEffect;
		break;
	case EffectKinds::Black_Bomb_Explosion:
		SAFE_RELEASE(body, imageInfo);
		body = new BlackBombExplosionEffect;
		break;
	case EffectKinds::Blue_Projectlie:
		SAFE_RELEASE(body, imageInfo);
		body = new PulsateEffect;
		{
			Actor* actor = Cast<Actor>(owner);
			const float* asdf = actor->GetAngle_ptr();
			if (actor)
				Cast<PulsateEffect>(body)->SetonwerAngle(asdf);
		}
		break;
	}

}

HRESULT Effect::Init()
{
	IMAGEMANAGER->LoadPng(L"effect_a",L"Effect/effect_a");
	imageInfo.imageName = L"effect_a";
	imageInfo.imageLocation = { -10.0f,-10.f };
	imageInfo.atlasInfo.frameSize = { 31.0f,31.0f };
	imageInfo.imageEffect = D2DIE_DEFAULT | D2DIE_EXPOSUREEFFECT;
	return S_OK;
}

void Effect::Release()
{
	Super::Release();
	SAFE_RELEASE(body, imageInfo);
}

void Effect::Update()
{
	Super::Update();
	if (owner)
		location = owner->GetLocation();
	if (body)
		body->Update(imageInfo);
	imageInfo.imageLocation = location;
	
}

void Effect::Render()
{
	Super::Render();
	IMAGEMANAGER->ImageRander(imageInfo);
	if (body)
		body->Render(imageInfo);
}
