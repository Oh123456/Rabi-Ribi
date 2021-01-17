#include "LoadingScene.h"

HRESULT LoadingScene::Init()
{
	IMAGEMANAGER->LoadPng(L"loadcg0_a",L"loadcg0_a");
	imageInfo.imageName = L"loadcg0_a";
	imageInfo.imageEffect = D2DIE_SCALE;
	ID2D1Bitmap* loading = IMAGEMANAGER->FindImage(L"loadcg0_a");
	D2D1_SIZE_U size = loading->GetPixelSize();
	D2D1_SIZE_F scaleSize = { WINSIZE_X / size.width , WINSIZE_Y / size.height };
	imageInfo.scaleInfo.scaleSize = scaleSize;
	imageInfo.scaleInfo.scaleCenterPoint = { 0.0f,0.0f };
	imageInfo.imageLocation = { WINSIZE_X / 2.0f, WINSIZE_Y / 2.0f - 50.0f };
	return S_OK;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
}

void LoadingScene::Render()
{
	IMAGEMANAGER->ImageRander(imageInfo);
}
