#include "Actor.h"
#include "GeometryCollision.h"
#include "D2DGraphic.h"


void Actor::Update()
{
	Super::Update();
	if ((worldLocation.x == 0.0f) & (worldLocation.y == 0.0f))
		worldLocation = location;
	cameraLocation = CAMERA->GetLocation();
	location.x = { worldLocation.x - cameraLocation.x };
	location.y = { worldLocation.y - cameraLocation.y };
	geomtryLocation.x = { worldLocation.x - cameraLocation.x };
	geomtryLocation.y = { worldLocation.y - cameraLocation.y };
}

void Actor::Release()
{
	Super::Release();
	SAFE_RELEASE(collisionGeomtry);
	SAFE_RELEASE(hitBoxCollisionGeomtry);
}

void Actor::SetCollisionGeometry(const ID2D1PathGeometry * const collisionGeomtry)
{
	this->collisionGeomtry->SetCollision(Cast<ID2D1PathGeometry>(collisionGeomtry),this);
}

void Actor::SetGeomtryLocation(const Location & letfTopLocation, const SIZE_F & size)
{
	this->geomtryLocation.x = letfTopLocation.x + (size.width / 2.0f);
	this->geomtryLocation.y = letfTopLocation.y + (size.height / 2.0f);
}

const ID2D1PathGeometry* Actor::GetCollisionPathGeomtry()
{
	return this->collisionGeomtry->GetGeometry();
}

Location Actor::GetLTLocation()
{
	return { location.x - (size.width / 2) , location.y - (size.height / 2) };
}

void Actor::SetGeomtryCollsion()
{
	ID2D1PathGeometry* collsion;
	D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&collsion);
	ID2D1GeometrySink* sink = NULL;
	collsion->Open(&sink);

	sink->BeginFigure({ 0,size.height }, D2D1_FIGURE_BEGIN_FILLED);
	D2D1_POINT_2F point[3] = { {size.width,size.height},
								{size.width,0.0f},
								{0.0f,0.0f} };
	sink->AddLines(point, 3);
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();
	sink->Release();


	collisionGeomtry = new GeometryCollision;

	collisionGeomtry->SetCollision(collsion, this);
	geomtryLocation = location;

	if ((hitBoxSize.width == -1.0f) & (hitBoxSize.height == -1.0f))
		hitBoxSize = size;

	ID2D1PathGeometry* hitBoxPathCollsion = nullptr;
	D2D::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&hitBoxPathCollsion);
	ID2D1GeometrySink* sink2 = NULL;
	hitBoxPathCollsion->Open(&sink2);

	sink2->BeginFigure({ 0,hitBoxSize.height }, D2D1_FIGURE_BEGIN_FILLED);
	D2D1_POINT_2F point2[3] = { {hitBoxSize.width,hitBoxSize.height},
								{hitBoxSize.width,0.0f},
								{0.0f,0.0f} };
	sink2->AddLines(point2, 3);
	sink2->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink2->Close();
	sink2->Release();


	hitBoxCollisionGeomtry = new GeometryCollision;

	hitBoxCollisionGeomtry->SetCollision(hitBoxPathCollsion, this);
	hitBoxCollisionGeomtry->SetCollisionSize(hitBoxSize);

}
