#pragma once
#include "Object.h"
// ��� �ɵ� �ϴ� ����
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

