#pragma once
#include "Object.h"

DELEGATE_OneParam(OnHit, Object*);

// 게임에 소환되에 그려지는 객체들
class Actor : public Object
{
	SUPER(Object);
public:
	Actor() : collisionGeomtry(nullptr){}
	~Actor() {}
	inline void SetCollisionGeometry(const ID2D1PathGeometry* const collisionGeomtry)		{ this->collisionGeomtry = const_cast<ID2D1PathGeometry*>(collisionGeomtry); }
	inline void SetLocation(const Location& location)													{ this->location = location; }
	void SetGeomtryLocation(const Location& letfTopLocation, const SIZE_F& size);
	inline void SetGeomtryLocation(const Location& location)										{ this->geomtryLocation = location; }
	inline void SetSize(const SIZE_F& size)																{ this->size = size; }



	inline const ID2D1PathGeometry* GetCollisionGeomtry()									const { return this->collisionGeomtry; }
	inline const Location& GetLocation()															const { return this->location; }
	inline const Location& GetGeomtryLocation()												const { return this->geomtryLocation; }
	inline const SIZE_F& GetSize()																	const { return this->size; }
public:
	// 콜리전 충돌
	OnHit onHit;
protected:
	// 위치
	Location location;
	SIZE_F size;
	// 충돌영역
	ID2D1PathGeometry* collisionGeomtry;
	Location geomtryLocation;

	class TexturesComponent* body;
};

