#include "MoveActor.h"
#include "D2DGraphic.h"
#include "PlayScene.h"
#include "Stage.h"
#include "Erina.h"

MoveActor::MoveActor()
{
	onHit.BindObject(this,&MoveActor::OnHit);
}

MoveActor::~MoveActor()
{
}

HRESULT MoveActor::Init()
{
	size = { 32.0f  ,32.0f };
	hitBoxSize = { 64.0f,64.0f };
	SetGeomtryCollsion();
	return S_OK;
}

void MoveActor::Release()
{
	Super::Release();
	SAFE_DELETE(moveStage);
}

void MoveActor::Update()
{
	Super::Update();
}

void MoveActor::Render()
{
#ifdef _DEBUG
	Super::Render();
	ID2D1SolidColorBrush* brush = D2D::GetSingleton()->GetBrush();
	brush->SetColor(D2D1::ColorF(0xff0000, 1.0f));
	D2D::GetSingleton()->GetD2DRenderTarget()->DrawRectangle({ location.x - size.width / 2, location.y - size.height / 2 ,
																location.x + size.width / 2, location.y + size.height / 2 }, brush);
	
#endif // _DEBUG
}

void MoveActor::OnHit(Object * obejct)
{
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		if (Cast<Erina>(obejct))
		{
			playScene->ChangeScene("Å×½ºÆ®¸Ê");
		}
	}
}
