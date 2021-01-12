#include "Projectile.h"
#include "ProjectileAnimInstance.h"
#include "Character.h"
#include "Effect.h"
#include "D2DGraphic.h"
#include "TileMap.h"

Projectile::Projectile() : 
	angle(0.0f), speed(0.0f,0.0f) , animKinds(ProjectileAnimationKinds::Circle_Red)
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
		DeleteChild(Cast<Effect>(effect));	
	if (imageInfo.imageEffect & D2DIE_NOIMAGE)
		RemoveImageEffect(imageInfo,D2DIE_NOIMAGE);
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
		if ((this != object) & (owner != object) & (Cast<Actor>(object)->GetActorType() != ActorType::Weapone))
		{
			this->SetIsValid(false);
			Character* character = Cast<Character>(object);
			if (character)
				character->TakeDamage(100);
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
