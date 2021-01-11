#pragma once
#include "Object.h"

struct ActorKey_Value
{
	class Actor*  actor;

	bool operator <(const ActorKey_Value& sru) const
	{
		if (this->actor < sru.actor)
			return true;
		return false;
	}
};


class CollisionManager : public Object
{
	SUPER(Object);
public:
	CollisionManager();
	~CollisionManager();
	

	//  멤버 변수 초기화, 메모리 할당
	HRESULT Init() override;
	// 메모리 해제
	void Release() override;
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	void Update() override;
	// 프레임 단위 출력 (이미지, 텍스트)
	void Render() override;

	void SettingActor(Object* secen);

	void TerrainCollisionCheck();

private:
	void TerrainBottomCollision(class Actor* actor, UINT tileX_Size, Location& player_LTLocation);
	bool TerrainSideCollision(class Actor* actor, UINT tileX_Size, Location& player_LTLocation);
	bool TerrainTopCollision(class Actor* actor, UINT tileX_Size, const Location& player_LTLocation);

	void ActorCollision();
	void ActorCollision(list<Actor*>& splitCollision);
	// 4분할
	void SplitScreen();
	void TerrainProjetileleCollision(class Projectile* projectile, UINT tileX_Size);
private:
	// 충돌 검사할 액터
	set<ActorKey_Value> actors;
	class TileMap* tileMap;

	list<Actor*> collision[4];
	// AI 센서 콜리전
	list<Actor*> sensorCollision[4];

	class GeometryCollision* SideCollosion[2];
	class GeometryCollision* battomCollosion[4];
	class GeometryCollision* topCollosion[3];
#ifdef _DEBUG
	list<GeometryCollision*> debug_collisionBoxlist;
#endif // _DEBUG
};

