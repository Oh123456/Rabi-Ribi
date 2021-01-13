#include "CatAIController.h"
#include "PlayScene.h"
#include "Character.h"
#include "CatHelicopter.h"


CatAIController::CatAIController()
{
}

CatAIController::~CatAIController()
{
}

HRESULT CatAIController::Init()
{
	return E_NOTIMPL;
}

void CatAIController::Release()
{
	Super::Release();
}

void CatAIController::Update()
{
	Super::Update();
	if (KEYMANAGER->IsOnceKeyDown(_1Key))
	{
		PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
		MoveToLocation(playScene->GetPlayer()->GetWorldLocation());
	}
	if (KEYMANAGER->IsOnceKeyDown(_2Key))
	{
		CatHelicopter* cat = Cast<CatHelicopter>(owner);
		cat->NomalAttack();
	}
}

void CatAIController::Render()
{
}
