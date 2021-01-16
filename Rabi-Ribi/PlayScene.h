#pragma once
#include "Object.h"
class PlayScene : public Object
{
	SUPER(Object)
public:
	PlayScene();
	~PlayScene();
	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;

	class ProjectileManager* GetProjectileManager() { return projectileManager; }
	class Actor* GetPlayer() { return player; }
private:
	ImageInfo testbg;
	class Actor* player;
	class Actor* cocoa;
	class TileMap* mainTile;
	class Stage* stage;
	class ProjectileManager* projectileManager;
	class HUD* hud;
};

