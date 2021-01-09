#include "Projectile.h"
#include "ProjectileAnimInstance.h"
#include "Character.h"
#include "Effect.h"

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
	imageInfo.imageLocation = { 300.f,300.f };
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
	Location cameraLocation = CAMERA->GetLocation();
	location.x = { worldLocation.x - cameraLocation.x };
	location.y = { worldLocation.y - cameraLocation.y };
	geomtryLocation.x = { worldLocation.x - cameraLocation.x };
	geomtryLocation.y = { worldLocation.y - cameraLocation.y };

	if (vcMovePatten[Cast<int>(movePatten)])
		(this->*vcMovePatten[Cast<int>(movePatten)])();
	imageInfo.imageLocation = location;
}

void Projectile::Render()
{
	Super::Render();

}

void Projectile::SetIsValid(bool value)
{
	Super::SetIsValid(value);
	// 생성된 이펙트를 제거한다.
	Object::Release();
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

	if ((this != object) & (owner != object) & (Cast<Actor>(object)->GetActorType() != ActorType::Weapone))
	{
		this->SetIsValid(false);
		Character* character = Cast<Character>(object);
		if (character)
			character->TakeDamage(100);
	}
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
