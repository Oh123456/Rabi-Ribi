#include "MainGame.h"
#include "D2DGraphic.h"
#include "TileMapToolScene.h"
#include "TestRoom.h"

HRESULT MainGame::Init()
{
	ImageManager* imageManager = IMAGEMANAGER;
	imageManager->Init();
	imageManager->SetDefaultDirectory(L"Image/");
	KEYMANAGER->Init();
	TIMERMANAGER->Init();
	SOUNDMANAGER->Init();
	SceneManager* scenManager = SCENEMANAGER;
	scenManager->Init();

	// 대부분에서 사용할 이미지를 넣어둔다
	imageManager->LoadPng(L"샘플타일", L"Tile/tile1_a");
	
	scenManager->AddScene("맵툴씬", CreateScene<TileMapToolScene>());
	scenManager->AddScene("테스트룸", CreateScene<TestRoom>());

	scenManager->ChangeScene("맵툴씬");
	
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
}

void MainGame::Update()
{
	Super::Update();
	TIMERMANAGER->Update();

	if (KEYMANAGER->IsOnceKeyUP(VK_F1))
		isFPS = !isFPS;
}



void MainGame::Render()
{
	Super::Render();
	static int j = 0;
	static float a = 0.0f;
	static int R = 0;
	static int countss = 8;
	ImageInfo imageInfo;

	imageInfo.imageName = L"player_a";
	imageInfo.imageLocation = { 500,300 };
	imageInfo.atlasInfo.frameSize = { 64,64 }; //= { (64.0f * j),0.0f + (0 * 64.0f), 64.0f + (64.0f * j),64.0f + (0 * 64.0f) };
	imageInfo.atlasInfo.frame = { j, 0 };
	//imageInfo.atlasSize = { (64.0f * j),0.0f + (0 * 64.0f), 64.0f + (64.0f * j),64.0f + (0 * 64.0f) };
	imageInfo.affineMatrix = Matrix3x2F::Rotation(3.5, { 32.0f ,32.0f });
	imageInfo.tintColor = D2D1::Vector4F(1.0f, 1.f, 1.0f, 1.0f);
	imageInfo.spotDiffuseInfo.lightPoint = D2D1::Vector3F(64.0f, 0.0f, 0.5f);
	imageInfo.contrasteInfo.contrast = -1.0f;
	imageInfo.temperatureInfo.temperature = 2.0f;
	imageInfo.temperatureInfo.tint = 1.0f;
	imageInfo.scaleInfo.scaleSize = { 1.0f ,1.0f };
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_CONTRASTEFFECT | D2DIE_AFFINE;
	ImageManager::GetSingleton()->ImageRander(imageInfo);

	GETMANAGER(ImageManager);

	a += 1.0f;
	if (a >= 360.0f)
		a = 0.f;
	static int zz = 0;
	zz++;
	if (zz == 8)
	{
		j++;
		if (j == countss)
			j = 0;
		zz = 0;
	}


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
