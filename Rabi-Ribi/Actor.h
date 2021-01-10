#pragma once
#include "Object.h"
#include "AIBase.h"

DELEGATE_OneParam(OnHit, Object*);

enum class ActorType
{
	Enemy,
	Player,
	Weapone,
	None,
};


// 게임에 소환되에 그려지는 객체들
class Actor : public Object
{
	SUPER(Object);
public:
	Actor() : collisionGeomtry(nullptr), AIController(nullptr), IgnoreTerrain(false), hitBoxSize({-1.0f,-1.0f}), actorType(ActorType::None) {}
	~Actor() {}

	void Update()	override;
	void Release()	override;

	void SetCollisionGeometry(const ID2D1PathGeometry* const collisionGeomtry);
	inline void SetWorldLocation(const Location& location)												{ this->worldLocation = location; }
	inline void SetLocation(const Location& location)													{ this->location = location; }
	inline void SetLocation(const Location& location, const Location& worldlocation)					{ this->SetLocation(location); this->SetWorldLocation(worldlocation);}
	void SetGeomtryLocation(const Location& letfTopLocation, const SIZE_F& size);
	inline void SetGeomtryLocation(const Location& location)										{ this->geomtryLocation = location; }
	inline void SetSize(const SIZE_F& size)																{ this->size = size; }


	inline class GeometryCollision* GetHitBoxCollisionGeomtry()									const { return this->hitBoxCollisionGeomtry; }
	inline class GeometryCollision* GetCollisionGeomtry()										const { return this->collisionGeomtry; }
	const ID2D1PathGeometry* GetCollisionPathGeomtry();
	Location GetLTLocation();
	inline const Location& GetLocation()															const { return this->location; }
	inline const Location& GetWorldLocation()															const { return this->worldLocation; }
	inline const Location& GetGeomtryLocation()												const { return this->geomtryLocation; }
	inline const SIZE_F& GetSize()																	const { return this->size; }
	inline const ImageInfo* GetImageInfo_ptr()															{ return &this->imageInfo;}
	inline bool GetIgnoreTerrain()																	const { return IgnoreTerrain; }
	inline class Animinstance* GetAnimInstance()												const { return animmation; }
	inline ActorType GetActorType()																const { return actorType; }
protected:
	void SetGeomtryCollsion();

	template<class UserClass>
	Object* CreateAIController()
	{
		AIController = CreateObject<UserClass>();
		AIController->SetOwner(this);
		return AIController;
	}
public:
	// 콜리전 충돌
	OnHit onHit;
protected:
	// 위치
	Location location;
	SIZE_F size;
	SIZE_F hitBoxSize;
	// 충돌영역
	class GeometryCollision* collisionGeomtry;
	class GeometryCollision* hitBoxCollisionGeomtry;
	//ID2D1PathGeometry* collisionGeomtry;
	Location geomtryLocation;

	// 이미지
	ImageInfo imageInfo;
	class Animinstance* animmation;
	bool IgnoreTerrain;

	class AIBase* AIController;
	ActorType actorType;

	Location worldLocation;
	// 충돌처리 전까지 플레이어가 움직이면 카메라의 좌표가 
	//변함으로 실제 위치와 다르게 되서 처음 위치구했을때의 
	//값을 저장해둔 변수
	Location cameraLocation;


};

