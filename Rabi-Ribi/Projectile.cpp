#include "Projectile.h"
#include "ProjectileAnimInstance.h"
#include "Character.h"
#include "Effect.h"
#include "D2DGraphic.h"
#include "TileMap.h"
#include "Erina.h"

Projectile::Projectile() :
	speed(0.0f, 0.0f), animKinds(ProjectileAnimationKinds::Circle_Red), addAngle(0.261799f)
{
	IgnoreTerrain = false;
	animmation = CreateObject<ProjectileAnimInstance>();
	animmation->SetOwner(this);
	onHit.BindObject(this,&Projectile::OnHit);

	vcMovePatten.resize(MovePattenEnd);
	for (int i = 0; i < MovePattenEnd; i++)
		vcMovePatten[i] = nullptr;
	int i = 0;
	vcMovePatten[i++] = &Projectile::NomalMovePatten;
	vcMovePatten[i++] = &Projectile::AngleMovePatten;
	vcMovePatten[i++] = &Projectile::AngleTunMovePatten;
	vcMovePatten[i++] = &Projectile::AngleTunMoveAngleChangePatten;
}

HRESULT Projectile::Init()
{
	IMAGEMANAGER->LoadPng(L"projectile", L"Projectile/projectile_a");
	imageInfo.imageName = L"projectile";
	imageInfo.imageLocation = { 0,0 };
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_AFFINE;
	imageInfo.atlasInfo.frame = { 0,0 };
	imageInfo.atlasInfo.frameSize = { 62.0,31.0f };
	imageInfo.affineMatrix = Matrix3x2F::Scale({ 0.5f,0.5f }, {31.0f,15.5f});
	size = { 64.0f  ,31.0f };

	SetGeomtryCollsion();
	defaultImageInfo = imageInfo;
	//projectile_a
	return S_OK;
}

void Projectile::Release()
{
	Super::Release();
}

void Projectile::Update()
{
	Super::Update();
}

void Projectile::Render()
{
	Super::Render();
}

void Projectile::SetIsValid(bool value)
{
	Super::SetIsValid(value);
	if (!value)
		location = { -10.0f,-10.0f };
	else
		worldLocation = { 0.0f,0.0f };
	// 생성된 이펙트를 제거한다.

	if (!value)
	{
		imageInfo = defaultImageInfo;
		DeleteChild(Cast<Effect>(effect));
		effect = nullptr;

		// 임시
		if (Cast<Erina>(owner))
			Cast<Erina>(owner)->SetDamage(15);
	}
	angle = 0.0f;
	//:
	if (TIMERMANAGER->ExistTimer(angleTunTimer))
	{
		TIMERMANAGER->DeleteTimer(angleTunTimer);
		angleTunTimer.timerNum = 0;
	}
	imageInfo.imageEffect = D2DIE_DEFAULT;
	//if (imageInfo.imageEffect & D2DIE_NOIMAGE)
	//	RemoveImageEffect(imageInfo,D2DIE_NOIMAGE);
}

void Projectile::MoveSetting(float angle, Vector2_F speed, MovePatten movePatten)
{
	this->angle = angle;
	this->speed = speed;
	this->movePatten = movePatten;
}

void Projectile::CreateEffect()
{
	if (!effect)
		effect = CreateObject<Effect>();
	effect->SetOwner(this);
}

void Projectile::OnHit(Object* object)
{
	if (Cast<TILE_F>(object))
		this->SetIsValid(false);
	else
	{
		if ((this != object) & (owner != object) & (Cast<Actor>(object)->GetActorType() != ActorType::Weapone) & (owner->GetActorType() != Cast<Actor>(object)->GetActorType()))
		{
			this->SetIsValid(false);
			Character* character = Cast<Character>(object);
			if (character)
			{
				// 임시
				if (Cast<Erina>(owner))
					Cast<Erina>(owner)->SetDamage(15);
				character->TakeDamage(Cast<Character>(owner)->GetDamage());
			}
		}
	}

}

void Projectile::MoveMent()
{
	if (vcMovePatten[Cast<int>(movePatten)])
		(this->*vcMovePatten[Cast<int>(movePatten)])();
	if ((geomtryLocation.x < -50.0f) | (geomtryLocation.x > (D2D::GetSingleton()->GetD2DRenderTarget()->GetPixelSize().width / CAMERA->GetZoom().x)) |
		(geomtryLocation.y < -50.0f) | (geomtryLocation.y > (D2D::GetSingleton()->GetD2DRenderTarget()->GetPixelSize().height / CAMERA->GetZoom().y)))
		this->SetIsValid(false);
}


void Projectile::NomalMovePatten()
{
	geomtryLocation.x += speed.x;
	location.x = geomtryLocation.x;
}

void Projectile::AngleMovePatten()
{
	geomtryLocation.x += cosf(this->angle) * speed.x;
	geomtryLocation.y += sinf(this->angle) * speed.y;
	location = geomtryLocation;

}

void Projectile::AngleTunMovePatten()
{
	if (!TIMERMANAGER->ExistTimer(angleTunTimer))
		TIMERMANAGER->SetTimer(angleTunTimer,this,&Projectile::AngleTun,0.8f,false);
	geomtryLocation.x += cosf(this->angle) * speed.x;
	geomtryLocation.y += sinf(this->angle) * speed.y;
	location = geomtryLocation;
}

void Projectile::AngleTunMoveAngleChangePatten()
{
	if (!TIMERMANAGER->ExistTimer(angleTunTimer))
		TIMERMANAGER->SetTimer(angleTunTimer, this, &Projectile::AngleTunAngleChange, 0.4f, false);
	geomtryLocation.x += cosf(this->angle) * speed.x;
	geomtryLocation.y += sinf(this->angle) * speed.y;
	location = geomtryLocation;
}

void Projectile::AngleTun()
{
	angle += PI;
	imageInfo.affineMatrix = imageInfo.affineMatrix * Matrix3x2F::Rotation(180.f, { imageInfo.atlasInfo.frameSize.width / 2.0f,imageInfo.atlasInfo.frameSize.height / 2.0f });
	TIMERMANAGER->SetTimer(angleTunTimer, this, &Projectile::AngleTun,6000.0f);
	speed.x *= 1.5f;
	speed.y *= 1.5f;
}

void Projectile::AngleTunAngleChange()
{
	angle += PI + addAngle;
	imageInfo.affineMatrix = imageInfo.affineMatrix * Matrix3x2F::Rotation(180.f, { imageInfo.atlasInfo.frameSize.width / 2.0f,imageInfo.atlasInfo.frameSize.height / 2.0f });
	TIMERMANAGER->SetTimer(angleTunTimer, this, &Projectile::AngleTun, 6000.0f);
	speed.x *= 1.5f;
	speed.y *= 1.5f;
}

void Projectile::TagetMove()
{
	Vector2_F _location = location;
	Vector2_F goalLocation = _location - tagetLocation;
	float angle = atan2f(goalLocation.y, goalLocation.x);
	geomtryLocation.x += cosf(this->angle) * speed.x;
	geomtryLocation.y += sinf(this->angle) * speed.y;
}

void Projectile::DeleteEffect()
{


	
	list<Object*>::const_iterator uit;
	Object* a;
	for (uit = allClass.begin(); uit != allClass.end(); uit++)
	{
		a = *uit;
		if (Cast<Effect>(a))
		{
			allClass.erase(uit);
			SAFE_RELEASE(a);
			break;
		}
	}

}
