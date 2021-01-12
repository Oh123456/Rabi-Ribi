#include "CarrotBomb.h"
#include "TileMap.h"
#include "CarrotBombExplosionEffect.h"
#include "Character.h"

CarrotBomb::CarrotBomb()
{
}

CarrotBomb::~CarrotBomb()
{
}

HRESULT CarrotBomb::Init()
{
	Super::Init();
	worldLocation = { 0.0f,0.0f };
	size = { 31.0f * 0.5f ,31.0f * 0.5f };
	hitBoxSize = size;
	SetGeomtryCollsion();

	CreateEffect();
	effect->SetEffect(EffectKinds::Carrot_Bomb);
	isExplosion = false;
	imageInfo.imageLocation = { 0.0f,0.0f };
	return S_OK;
}

void CarrotBomb::Release()
{
	Super::Release();
}

void CarrotBomb::Update()
{
	Super::Update();
	if (isExplosion)
	{
		Effect* effectBody = Cast<Effect>(effect);
		CarrotBombExplosionEffect* bombEffect = Cast<CarrotBombExplosionEffect>(effectBody->GetEffect());
		if (bombEffect->GetIsEnd())
			SetIsValid(false);
	}

}

void CarrotBomb::Render()
{
	Super::Render();
}

void CarrotBomb::Explosion()
{
	if (effect)
	{
		effect->SetEffect(EffectKinds::Carrot_Bomb_Explosion);
		Effect* effectBody = Cast<Effect>(effect);
		ImageInfo* effectimageInfo = Cast<ImageInfo>(effectBody->GetImageInfo_ptr());
		effectimageInfo->atlasInfo.frameSize = { 100.0f,60.f };
		effectimageInfo->imageEffect = D2DIE_NOIMAGE;
		size = { 100.0f,60.f };
		hitBoxSize = size;
		SetGeomtryCollsion();
		acceleration = 0.0f;
		speed = { 0.0f,0.0f };

		onHit.UnBind();
		onHit.BindObject(this,&CarrotBomb::ExplosionHit);
		isExplosion = true;
	}
}

void CarrotBomb::ExplosionHit(Object * object)
{
	if ((object != this))
	{
		Character* acotr = Cast<Character>(object);
		if (acotr)
		{
			if (acotr->GetActorType() == ActorType::Enemy)
			{
				acotr->TakeDamage(damage);
			}
		}
	}

}
