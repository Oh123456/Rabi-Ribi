#pragma once
#include"ObjectBase.h"


class GeometryCollision
{
public:
	GeometryCollision();
	~GeometryCollision();

	void Release();

	void SetCollision(ID2D1PathGeometry* geometry, const ObjectBase* object);
	Matrix3x2F GetTranslationMatrix3x2F(const Location& objectLocation);
	Location GetOwnerLocation();

	D2D1_GEOMETRY_RELATION CollisionCheck(ID2D1PathGeometry* geometry, const Location& objectLocation);
	bool CollisionHitCheck(ID2D1PathGeometry* geometry, const Location& objectLocation);
	GeometryInfo info;

	ID2D1PathGeometry* geometry;
	const ObjectBase* owner;
};

