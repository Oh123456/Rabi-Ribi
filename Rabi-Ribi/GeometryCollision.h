#pragma once
#include "pch.h"


class GeometryCollision
{
public:
	GeometryCollision();
	~GeometryCollision();

	void Release();

	void SetCollision(ID2D1PathGeometry* geometry, const class Actor* object);
	void SetCollision(ID2D1PathGeometry* geometry, const SIZE_F& size ,const class Actor* object);
	void SetCollisionSize(const SIZE_F& size) { collisionSize = size; }
	void SetGeometryInfo(const GeometryInfo& info) { this->info = info; }
	const GeometryInfo& GetGeometryInfo() { return this->info; }
	Matrix3x2F GetTranslationMatrix3x2F(const Location& objectLocation);
	Location GetOwnerLocation();
	ID2D1PathGeometry* GetGeometry() const {return geometry;}
	// 디버깅용 랙트사좌표 반환
	D2D_RECT_F GetGeometryRect();

	D2D1_GEOMETRY_RELATION CollisionCheck(ID2D1PathGeometry* geometry, const Location& objectLocation);
	bool CollisionHitCheck(ID2D1PathGeometry* geometry, const Location& objectLocation);


	const class Actor* GetOwner() { return owner; }

private:
	GeometryInfo info;
	ID2D1PathGeometry* geometry;
	const class Actor* owner;
	SIZE_F collisionSize;
};

