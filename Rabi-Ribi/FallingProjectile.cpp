#include "FallingProjectile.h"
#include "TileMap.h"
#include "D2DGraphic.h"

FallingProjectile::FallingProjectile()
{
	onHit.BindObject(this, &FallingProjectile::OnHit);
}

FallingProjectile::~FallingProjectile()
{
}

HRESULT FallingProjectile::Init()
{
	TIMERMANAGER->SetTimer(accelerationTimer, this, &FallingProjectile::Acceleration, 0.016f);
	return E_NOTIMPL;
}

void FallingProjectile::Release()
{
	Super::Release();
	TIMERMANAGER->DeleteTimer(accelerationTimer);
}

void FallingProjectile::Update()
{
	Super::Update();
}

void FallingProjectile::Render()
{
	Super::Render();
#ifdef _DEBUG
	ID2D1SolidColorBrush* brush = D2D::GetSingleton()->GetBrush();
	brush->SetColor(D2D1::ColorF(0xf0f00f, 1.0f));
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ location.x - size.width / 2, location.y - size.height / 2 ,
																location.x + size.width / 2, location.y + size.height / 2 }, brush);
#endif // _DEBUG
}

void FallingProjectile::SetSpeed(Vector2_F speed)
{
	Super::SetSpeed(speed);
	acceleration = speed.y;
}

void FallingProjectile::SetSpeed(float xValue)
{
	speed.x = xValue;
}

void FallingProjectile::SetIsValid(bool value)
{
	Super::SetIsValid(value);
	TIMERMANAGER->DeleteTimer(accelerationTimer);
	cameraLocation = { 0,0 };
}

void FallingProjectile::OnHit(Object* object)
{
	if (Cast<TILE_F>(object))
	{
		acceleration *= -0.5f;
		speed.x *= 0.5f;
	}
}

void FallingProjectile::MoveMent()
{
	geomtryLocation.x += speed.x;
	geomtryLocation.y += acceleration;
	location = geomtryLocation;
}

void FallingProjectile::MoveEnd(Location & worldLocation)
{
	location = geomtryLocation;
	worldLocation = { location.x + cameraLocation.x, location.y + cameraLocation.y };
	imageInfo.imageLocation = location;
}

void FallingProjectile::Acceleration()
{
	acceleration += (9.8f * 0.016f);
}
