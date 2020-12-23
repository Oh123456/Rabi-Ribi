#include "TestRoom.h"
#include "TileMap.h"
#include "D2DGraphic.h"

TestRoom::TestRoom()
{
}

TestRoom::~TestRoom()
{
}

HRESULT TestRoom::Init()
{
	TileMap* test =CreateObject<TileMap>();
	test->LoadTile("Save/Test1.map");

	IMAGEMANAGER->LoadPng(L"테스트배경",L"forest3_a");

	testbg.imageName = L"테스트배경";
	testbg.imageLocation = { 0.0f,0.0f };
	testbg.scaleInfo.scaleSize = { 3.0f,3.0f };
	testbg.imageEffect = D2DIE_SCALE;
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
	IMAGEMANAGER->ImageRander(testbg);
	Super::Render();
	static float a = 1.0f;
	D2D::GetSingleton()->GetD2DRenderTarget()->SetTransform(Matrix3x2F::Scale({ 2.0f,2.2f }));

}
