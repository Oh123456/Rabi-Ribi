#pragma once
#include "Object.h"
class PlayScene : public Object
{
	SUPER(Object)
public:
	PlayScene();
	~PlayScene();
	//  멤버 변수 초기화, 메모리 할당
	HRESULT Init() override;
	// 메모리 해제
	void Release() override;
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	void Update() override;
	// 프레임 단위 출력 (이미지, 텍스트)
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

