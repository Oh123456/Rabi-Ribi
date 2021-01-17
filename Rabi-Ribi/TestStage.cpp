#include "TestStage.h"
#include "TileMap.h"
#include "Rabbit.h"
#include "Wizard.h"
#include "Cocoa.h"

TestStage::TestStage()
{
}

TestStage::~TestStage()
{
}

HRESULT TestStage::Init()
{
	//backTile = CreateObject<TileMap>();
	//backTile->LoadTile("StartMap_Back.map");
	//middleTile = CreateObject<TileMap>();
	//middleTile->LoadTile("StartMap_Middle.map");
	mainTile = CreateObject<TileMap>();
	mainTile->LoadTile("test.map");

	return S_OK;
}

void TestStage::Release()
{
	Super::Release();
}

void TestStage::Update()
{
	Super::Update();
}

void TestStage::Render()
{
	Super::Render();
}
