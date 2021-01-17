#include "MainGame.h"
#include "D2DGraphic.h"
#include "TileMapToolScene.h"
#include "StartMapScene.h"
#include "BossMapScene.h"
#include "Character.h"
#include "LoadingScene.h"
#include "TitleScene.h"
#include <ctime>

HRESULT MainGame::Init()
{
	srand((UINT)time(NULL));
	ImageManager* imageManager = IMAGEMANAGER;
	imageManager->Init();
	imageManager->SetDefaultDirectory(L"\\Image\\");
	KEYMANAGER->Init();
	TIMERMANAGER->Init();
	SOUNDMANAGER->Init();
	SceneManager* scenManager = SCENEMANAGER;
	scenManager->Init();

	// ��κп��� ����� �̹����� �־�д�
	imageManager->LoadPng(L"����Ÿ��", L"Tile/tile1_a");
	
	scenManager->AddScene("������", CreateScene<TileMapToolScene>());
	scenManager->AddScene("���۸�", CreateScene<StartMapScene>());
	scenManager->AddScene("�׽�Ʈ��", CreateScene<BossMapScene>());
	scenManager->AddScene("Ÿ��Ʋ", CreateScene<TitleScene>());
	//scenManager->AddLoadingScene("�ε�", CreateScene<LoadingScene>());

	scenManager->ChangeScene("Ÿ��Ʋ");


	
#ifdef _DEBUG
	isFPS = true;
#else
	isFPS = false;
#endif // _DEBUG

	
	
	return S_OK;
}

void MainGame::Release()
{
	Super::Release();
	IMAGEMANAGER->Release();
	KEYMANAGER->Release();
	TIMERMANAGER->Release();
	SOUNDMANAGER->Release();
	SCENEMANAGER->Release();
}

void MainGame::Update()
{
	//CAMERA->Update();
	Super::Update();
	TIMERMANAGER->Update();
	if (KEYMANAGER->IsOnceKeyUP(VK_F1))
		isFPS = !isFPS;
	PlayScene* playScene = Cast<PlayScene>(SCENEMANAGER->currScene);
	if (playScene)
	{
		if (playScene->GetIsChage())
		{
			int HP = Cast<Character>(playScene->GetPlayer())->GetHP();
			SCENEMANAGER->ChangeScene(playScene->GetNextSceneName());
			PlayScene* newPlayScene = Cast<PlayScene>(SCENEMANAGER->currScene);
			if (newPlayScene)
			{
				Cast<Character>(newPlayScene->GetPlayer())->SetHP(HP);
			}
		}
	}



}



void MainGame::Render()
{
	Super::Render();
	//GETMANAGER(ImageManager);

}



void MainGame::MainLoop()
{
	D2D* d2d = D2D::GetSingleton();
	//ID2D1DeviceContext* Context = d2d->GetDeviceContext();
	d2d->BeginDraw();
	Render();

	if (isFPS)
		TIMERMANAGER->Render();
	d2d->EndDraw();
	Update();

}
