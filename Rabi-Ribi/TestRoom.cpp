#include "TestRoom.h"
#include "TileMap.h"

TestRoom::TestRoom()
{
}

TestRoom::~TestRoom()
{
}

HRESULT TestRoom::Init()
{
	TileMap* test =CreateObject<TileMap>();
	test->LoadTile("Save/QuickSave.map");
	return S_OK;
}

void TestRoom::Release()
{
	Super::Release();
}

void TestRoom::Update()
{
	Super::Update();
}

void TestRoom::Render()
{
	Super::Render();
}
