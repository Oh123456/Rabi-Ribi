#include "Actor.h"
#include "GeometryCollision.h"
#include "D2DGraphic.h"

void Actor::Release()
{
	Super::Release();
	SAFE_RELEASE(collisionGeomtry);
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

}
