#pragma once
#include "Object.h"

DELEGATE_OneParam(OnHit, Object*);

// ���ӿ� ��ȯ�ǿ� �׷����� ��ü��
class Actor : public Object
{
	SUPER(Object);
public:
	Actor() : collisionGeomtry(nullptr), IgnoreTerrain(false){}
	~Actor() {}

	void Release() override;

	void SetCollisionGeometry(const ID2D1PathGeometry* const collisionGeomtry);
	inline void SetLocation(const Location& location)													{ this->location = location; }
	void SetGeomtryLocation(const Location& letfTopLocation, const SIZE_F& size);
	inline void SetGeomtryLocation(const Location& location)										{ this->geomtryLocation = location; }
	inline void SetSize(const SIZE_F& size)																{ this->size = size; }


	inline class GeometryCollision* GetCollisionGeomtry()										const { return this->collisionGeomtry; }
	const ID2D1PathGeometry* GetCollisionPathGeomtry();
	inline const Location& GetLocation()															const { return this->location; }
	inline const Location& GetGeomtryLocation()												const { return this->geomtryLocation; }
	inline const SIZE_F& GetSize()																	const { return this->size; }
	inline const ImageInfo* GetImageInfo_ptr()															{ return &this->imageInfo;}
	inline bool GetIgnoreTerrain()																	const { return IgnoreTerrain; }
	inline class Animinstance* GetAnimInstance()												const { return animmation; }
protected:
	void SetGeomtryCollsion();
public:
	// �ݸ��� �浹
	OnHit onHit;
protected:
	// ��ġ
	Location location;
	SIZE_F size;
	// �浹����
	class GeometryCollision* collisionGeomtry;
	//ID2D1PathGeometry* collisionGeomtry;
	Location geomtryLocation;

	// �̹���
	ImageInfo imageInfo;
	class Animinstance* animmation;
	bool IgnoreTerrain;
};

