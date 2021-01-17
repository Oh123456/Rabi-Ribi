#include "TitleScene.h"

HRESULT TitleScene::Init()
{
	IMAGEMANAGER->LoadPng(L"title3_a",L"title3_a");
	IMAGEMANAGER->LoadPng(L"rabiribi_a", L"rabiribi_a");
	IMAGEMANAGER->LoadPng(L"start", L"start");
	bg.imageName = L"title3_a";
	bg.imageLocation = {WINSIZE_X / 2.0f,WINSIZE_Y / 2.0f - 50.0f };
	bg.scaleInfo.scaleSize = { 1.0f,1.25f };
	bg.imageEffect = D2DIE_SCALE;


	font.imageName = L"rabiribi_a";
	font.imageLocation = { WINSIZE_X / 2.0f,WINSIZE_Y / 2.0f - 150.0f };
	font.scaleInfo.scaleSize = { 1.0f,1.0f };
	font.imageEffect = D2DIE_SCALE;

	start.imageName = L"start";
	start.imageLocation = { WINSIZE_X / 2.0f,WINSIZE_Y / 2.0f + 200.0f };
	start.scaleInfo.scaleSize = { 1.0f,1.0f };
	start.imageEffect = D2DIE_SCALE;
	return S_OK;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
	//#ifdef _DEBUG
	if (KEYMANAGER->IsOnceKeyUP(VK_F2))
		SCENEMANAGER->ChangeScene("¸ÊÅø¾À");
	if (KEYMANAGER->IsOnceKeyUP(VK_RETURN))
		SCENEMANAGER->ChangeScene("½ÃÀÛ¸Ê");
	//#endif // _DEBUG
}

void TitleScene::Render()
{
	IMAGEMANAGER->ImageRander(bg);
	IMAGEMANAGER->ImageRander(font);
	IMAGEMANAGER->ImageRander(start);
}
