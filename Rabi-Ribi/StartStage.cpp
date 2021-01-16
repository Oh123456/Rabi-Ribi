#include "StartStage.h"
#include "TileMap.h"
#include "Rabbit.h"
#include "Wizard.h"
#include "Cocoa.h"

StartStage::StartStage()
{
}

StartStage::~StartStage()
{
}

HRESULT StartStage::Init()
{
	backTile = CreateObject<TileMap>();
	backTile->LoadTile("StartMap_Back.map");
	middleTile = CreateObject<TileMap>();
	middleTile->LoadTile("StartMap_Middle.map");
	mainTile = CreateObject<TileMap>();
	mainTile->LoadTile("StartMap.map");

	const list<TILE_F*>& spawnTile = mainTile->GetSpawnTileList();
	return S_OK;
}

void StartStage::Release()
{
	Super::Release();
}

void StartStage::Update()
{
	Super::Update();
}

void StartStage::Render()
{
	Super::Render();
}
