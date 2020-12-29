#pragma once
#include "pch.h"


class GeometryCollision
{
public:
	GeometryCollision();
	~GeometryCollision();

	void Release();

	void SetCollision(ID2D1PathGeometry* geometry, const class Actor* object);
	void SetGeometryInfo(const GeometryInfo& info) { this->info = info; }
	const GeometryInfo& GetGeometryInfo() { return this->info; }
	Matrix3x2F GetTranslationMatrix3x2F(const Location& objectLocation);
	Location GetOwnerLocation();
	ID2D1PathGeometry* GetGeometry() const {return geometry;}

	D2D1_GEOMETRY_RELATION CollisionCheck(ID2D1PathGeometry* geometry, const Location& objectLocation);
	bool CollisionHitCheck(ID2D1PathGeometry* geometry, const Location& objectLocation);


	const class Actor* GetOwner() { return owner; }

private:
	GeometryInfo info;
	ID2D1PathGeometry* geometry;
	const class Actor* owner;
};

