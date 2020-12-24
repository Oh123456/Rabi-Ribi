#include "GeometryCollision.h"
#include "Actor.h"

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
	SAFE_DELETE(owner)
}

void GeometryCollision::SetCollision(ID2D1PathGeometry* geometry, const ObjectBase* object)
{
	this->geometry = geometry;
	owner = object;
}

Matrix3x2F GeometryCollision::GetTranslationMatrix3x2F(const Location& objectLocation)
{
	Actor* actor = Cast<Actor>(owner);
	if (actor == nullptr)
		return Matrix3x2F();

	Location ownerLocation = { actor->GetLocation().x - (actor->GetSize().width) / 2,
								actor->GetLocation().y - (actor->GetSize().height) / 2 };

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


D2D1_GEOMETRY_RELATION GeometryCollision::CollisionCheck(ID2D1PathGeometry* geometry, const Location& objectLocation)
{
	D2D1_GEOMETRY_RELATION reuslt;
	this->geometry->CompareWithGeometry(geometry, GetTranslationMatrix3x2F(objectLocation), &reuslt);
	return reuslt;
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
		return false;
	case D2D1_GEOMETRY_RELATION_CONTAINS:
		return false;
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
