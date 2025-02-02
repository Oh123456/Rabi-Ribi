#include "Bomb.h"
#include "TileMap.h"
#include "Effect.h"


Bomb::Bomb() : 
	damage(100), isExplosion(false),
	isHit(false)
{
	
}

Bomb::~Bomb()
{
}

HRESULT Bomb::Init()
{
	Super::Init();
	imageInfo.imageName = L"projectile";
	//imageInfo.imageLocation = { 300.f,300.f };
	imageInfo.imageEffect = D2DIE_NOIMAGE;
	size = { 31.0f  ,31.0f };
	hitBoxSize = size;
	location = { 300.f,200.f };
	geomtryLocation = { 0.0f,0.0f };
	SetGeomtryCollsion();
	isHit = false;
	onHit.BindObject(this, &Bomb::OnHit);
	return S_OK;
}

void Bomb::Update()
{
	if (isExplosion)
		acceleration = 0.0f;
	Super::Update();
}

void Bomb::Release()
{
	Super::Release();
	TIMERMANAGER->DeleteTimer(explosionTimer);
}

void Bomb::OnHit(Object* object)
{
	Super::OnHit(object);
	if (Cast<TILE_F>(object))
	{
		if (!isHit)
		{
			isHit = true;
			TIMERMANAGER->SetTimer(explosionTimer, this, &Bomb::ExplosionTimer,0.5f);
		}
	}
}

void Bomb::ExplosionTimer()
{
	this->Explosion();
	TIMERMANAGER->DeleteTimer(explosionTimer);
}