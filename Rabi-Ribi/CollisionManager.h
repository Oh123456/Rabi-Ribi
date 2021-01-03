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
	

	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;

	void SettingActor(Object* secen);

	void TerrainCollisionCheck();

private:
	void TerrainBottomCollision(class Actor* actor, UINT tileX_Size, Location& player_LTLocation);
	bool TerrainSideCollision(class Actor* actor, UINT tileX_Size, Location& player_LTLocation);
	bool TerrainTopCollision(class Actor* actor, UINT tileX_Size, const Location& player_LTLocation);

	void ActorCollision();
private:
	// �浹 �˻��� ����
	set<ActorKey_Value> actors;
	class TileMap* tileMap;


	class GeometryCollision* SideCollosion[2];
	class GeometryCollision* battomCollosion[4];
	class GeometryCollision* topCollosion[3];
#ifdef _DEBUG
	list<GeometryCollision*> debug_collisionBoxlist;
#endif // _DEBUG
};

