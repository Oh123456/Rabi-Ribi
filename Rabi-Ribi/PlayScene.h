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

	void ChangeScene(string name) { isChage = true; nextSceneName = name; }
	GetSetFunction(IsChage,bool, isChage);
	GetSetFunction(NextSceneName, string, nextSceneName);
	class ProjectileManager* GetProjectileManager() { return projectileManager; }
	class Actor* GetPlayer() { return player; }
	class Actor* GetBoss() { return cocoa; }
protected:
	ImageInfo testbg;
	class Actor* player;
	class Actor* cocoa;
	class TileMap* mainTile;
	class Stage* stage;
	class ProjectileManager* projectileManager;
	class HUD* hud;
private:
	bool isChage;
	string nextSceneName;
};

