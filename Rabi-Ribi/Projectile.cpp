#include "Projectile.h"
#include "ProjectileAnimInstance.h"

Projectile::Projectile() : 
	angle(0.0f), speed(0.0f,0.0f) , animKinds(ProjectileAnimationKinds::Circle_Red)
{
	animmation = CreateObject<ProjectileAnimInstance>();
	animmation->SetOwner(this);

	vcMovePatten.resize(MovePattenEnd);
	for (int i = 0; i < MovePattenEnd; i++)
		vcMovePatten[i] = nullptr;
	int i = 0;
	vcMovePatten[i++] = &Projectile::NomalMovePatten;
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
	if (vcMovePatten[Cast<int>(movePatten)])
		(this->*vcMovePatten[Cast<int>(movePatten)])();
}

void Projectile::Render()
{
	Super::Render();

}

void Projectile::MoveSetting(float angle, Vector2_F speed, MovePatten movePatten)
{
	this->angle = angle;
	this->speed = speed;
	this->movePatten = movePatten;
}

void Projectile::OnHit(Object* object)
{
	if ((this != object) & (owner != object))
	{
		DEBUG_MASSAGE("ÃÑ¾Ë Ãæµ¹");
	}
}

void Projectile::NomalMovePatten()
{
	geomtryLocation.x += speed.x;
}
