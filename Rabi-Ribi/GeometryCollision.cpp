#include "GeometryCollision.h"
#include "Enemy.h"

GeometryCollision::GeometryCollision() : 
	geometry(nullptr) , owner(nullptr)
{

}

GeometryCollision::~GeometryCollision()
{
	this->Release();
}

void GeometryCollision::Release()
{
	SAFE_RELEASE(geometry)
	owner = nullptr;
}

void GeometryCollision::SetCollision(ID2D1PathGeometry* geometry, const Actor* object)
{
	this->geometry = geometry;
	owner = object;
	collisionSize = object->GetSize();
}

void GeometryCollision::SetCollision(ID2D1PathGeometry * geometry, const SIZE_F & size, const Actor * object)
{
	SetCollision(geometry, object);
	collisionSize = size;
}

Matrix3x2F GeometryCollision::GetTranslationMatrix3x2F(const Location& objectLocation)
{
	Actor* actor = Cast<Actor>(owner);
	if (actor == nullptr)
		return Matrix3x2F();

	Location ownerLocation = { actor->GetLocation().x - (collisionSize.width) / 2,
								actor->GetLocation().y - (collisionSize.height) / 2 };

	// 두 객체간의 차이를 행렬로 변환한다.
	Location result = { objectLocation.x - ownerLocation.x ,objectLocation.y - ownerLocation.y  };
	return Matrix3x2F::Translation(result.x, result.y);
}

Location GeometryCollision::GetOwnerLocation()
{

	Actor* actor = Cast<Actor>(owner);
	if (actor == nullptr)
		return Location();
	return actor->GetLocation();
}


D2D_RECT_F GeometryCollision::GetGeometryRect()
{
	Enemy* actor = Cast<Enemy>(owner);
	if (actor)
	{
		const Location& location = actor->GetLocation();
		const SIZE_F& size = actor->GetSeeAreaSize();
		D2D_RECT_F rect = { location.x - size.width / 2.0f, location.y - size.height / 2.0f,
								 location.x + size.width / 2.0f, location.y + size.height / 2.0f };
		return rect;

	}
	return D2D_RECT_F();
}

D2D1_GEOMETRY_RELATION GeometryCollision::CollisionCheck(ID2D1PathGeometry* geometry, const Location& objectLocation)
{
	if (geometry)
	{
		D2D1_GEOMETRY_RELATION reuslt;
		this->geometry->CompareWithGeometry(geometry, GetTranslationMatrix3x2F(objectLocation), &reuslt);
		return reuslt;
	}
	return D2D1_GEOMETRY_RELATION_UNKNOWN;
}

bool GeometryCollision::CollisionHitCheck(ID2D1PathGeometry* geometry, const Location& objectLocation)
{

	switch (CollisionCheck(geometry, objectLocation))
	{
	case D2D1_GEOMETRY_RELATION_UNKNOWN:
		return false;
	case D2D1_GEOMETRY_RELATION_DISJOINT:
		//DEBUG_MASSAGE("안곂침");
		return false;
	case D2D1_GEOMETRY_RELATION_IS_CONTAINED:
	case D2D1_GEOMETRY_RELATION_CONTAINS:
	case D2D1_GEOMETRY_RELATION_OVERLAP:
		return true;
		//DEBUG_MASSAGE("충돌");
	case D2D1_GEOMETRY_RELATION_FORCE_DWORD:
		return false;
	default:
		return false;
	}
	return false;
}
