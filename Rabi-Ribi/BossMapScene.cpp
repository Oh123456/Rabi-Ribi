#include "BossMapScene.h"
#include "TileMap.h"
#include "D2DGraphic.h"
#include "Erina.h"
#include "GeometryCollision.h"
#include "CollisionManager.h"
#include "PlayerInput.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "Effect.h"
#include "Cocoa.h"
#include "CarrotBomb.h"
#include "EnemyAIController.h"
#include "CatHelicopter.h"
#include "HUD.h"
#include "TestStage.h"

BossMapScene::BossMapScene()
{

}


BossMapScene::~BossMapScene()
{
}

HRESULT BossMapScene::Init()
{
	stage = CreateObject<TestStage>();
	mainTile = stage->GetMainTile();
	CollisionManager* collision = CreateObject<CollisionManager>(true);
	player = CreateObject<Erina>();
	cocoa = CreateObject<Cocoa>();
	IMAGEMANAGER->LoadPng(L"테스트배경", L"forest3_a");
	IMAGEMANAGER->LoadPng(L"Erina", L"Chacter/player_a");

	testbg.imageName = L"테스트배경";
	testbg.imageLocation = { 0.0f,0.0f };
	testbg.scaleInfo.scaleSize = { 3.0f,3.0f };
	testbg.imageEffect = D2DIE_SCALE;
	CAMERA->SetZoom({ 2.0f,2.2f });
	Cast<Character>(player)->PlayerInputSetting(CreateObject<PlayerInput>(false));
	projectileManager = CreateObject<ProjectileManager>();
	collision->SettingActor(this);
	hud = CreateObject<HUD>();

	CAMERA->SetFocusActor(player);
	return S_OK;
}

void BossMapScene::Release()
{
	Super::Release();
}

void BossMapScene::Update()
{
	Super::Update();
	EnemyAIController* ai = Cast<EnemyAIController>(Cast<Enemy>(cocoa)->GetAIController());
	if (ai->GetTaget() == nullptr)
		ai->SetTaget(player);
}

void BossMapScene::Render()
{
	Super::Render();
}
