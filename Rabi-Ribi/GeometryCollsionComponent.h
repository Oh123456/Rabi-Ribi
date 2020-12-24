#pragma once
#include "Object.h"
// 없어도 될듯 일단 보류
class GeometryCollisionComponent : public Object
{
public :
	GeometryCollisionComponent();
	~GeometryCollisionComponent();

	void SetCollision(ID2D1Geometry* collision) { this->collision = collision; }


	const ID2D1Geometry* GetCollision() const { return collision; }


private:
	ID2D1Geometry*  collision;
};

