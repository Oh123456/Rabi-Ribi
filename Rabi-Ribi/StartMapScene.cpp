#include "StartMapScene.h"
#include "TileMap.h"
#include "D2DGraphic.h"
#include "Erina.h"
#include "GeometryCollision.h"
#include "CollisionManager.h"
#include "PlayerInput.h"
#include "Rabbit.h"
#include "Wizard.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "Effect.h"
#include "Cocoa.h"
#include "CarrotBomb.h"
#include "EnemyAIController.h"
#include "CatHelicopter.h"
#include "HUD.h"
#include "StartStage.h"
#include "MoveActor.h"

StartMapScene::StartMapScene()
{

}

StartMapScene::~StartMapScene()
{
}

HRESULT StartMapScene::Init()
{
	stage = CreateObject<StartStage>();
	mainTile = stage->GetMainTile();
	CollisionManager* collision = CreateObject<CollisionManager>(true);
	player = CreateObject<Erina>();
	cocoa = nullptr;

	const list<TILE_F*>& moveTile = mainTile->GetMoveTileList();
	list<TILE_F*>::const_iterator c_it;
	for (c_it = moveTile.begin(); c_it != moveTile.end(); c_it++)
	{
		//if ((*c_it)->index.x == 0)
		{
			MoveActor* moveActor = CreateObject<MoveActor>();
			moveActor->SetWorldLocation({ (*c_it)->rc.left + 16.0f, (*c_it)->rc.top + 16.0f });
		}
	}

	const list<TILE_F*>& spawnTile = mainTile->GetSpawnTileList();
	Actor* actor;
	for (c_it = spawnTile.begin(); c_it != spawnTile.end(); c_it++)
	{
		switch (rand() % 3)
		{
		case 0:
		case 1:
			actor = CreateObject<Rabbit>();
			actor->SetGeomtryLocation({ (*c_it)->rc.left, (*c_it)->rc.top });
			actor->SetLocation({ (*c_it)->rc.left, (*c_it)->rc.top });
			break;
		default:
			actor = CreateObject<Wizard>();
			actor->SetGeomtryLocation({ (*c_it)->rc.left, (*c_it)->rc.top });
			actor->SetLocation({ (*c_it)->rc.left, (*c_it)->rc.top });
			break;
		}

	}
	
	
	//CreateObject<CatHelicopter>();
	//CreateObject<Rabbit>();
	//CreateObject<Wizard>();
	IMAGEMANAGER->LoadPng(L"테스트배경", L"forest3_a");
	IMAGEMANAGER->LoadPng(L"Erina", L"Chacter/player_a");

	testbg.imageName = L"테스트배경";
	testbg.imageLocation = { 0.0f,0.0f };
	testbg.scaleInfo.scaleSize = { 3.0f,3.0f };
	testbg.imageEffect = D2DIE_SCALE;
	CAMERA->SetZoom({ 2.0f,2.2f });
	//D2D::GetSingleton()->GetD2DRenderTarget()->SetTransform(Matrix3x2F::Scale({ 2.0f,2.2f }));
	Cast<Character>(player)->PlayerInputSetting(CreateObject<PlayerInput>(false));
	projectileManager = CreateObject<ProjectileManager>();
	collision->SettingActor(this);
	hud = CreateObject<HUD>();

	CAMERA->SetFocusActor(player);
	return S_OK;
}

void StartMapScene::Release()
{
	Super::Release();
}

void StartMapScene::Update()
{
	Super::Update();

}

void StartMapScene::Render()
{
	Super::Render();
}
