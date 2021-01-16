#include "HUD.h"
#include "PlayerHPBar.h"
#include "PlayScene.h"
#include "Character.h"
#include "BossHPBar.h"

HUD::HUD()
{
}

HUD::~HUD()
{
}

HRESULT HUD::Init()
{
	SetZOrder(1);
	playerHPBar = CreateObject<PlayerHPBar>();
	bossHPBar = CreateObject<BossHPBar>();
	return S_OK;
}

void HUD::Release()
{
	Super::Release();
}

void HUD::Update()
{
	Super::Update();
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
	{
		playerHPBar->BindCharacter(Cast<Character>(playScene->GetPlayer()));
		bossHPBar->BindCharacter(Cast<Character>(playScene->GetPlayer()));
	}


}

void HUD::Render()
{
	Super::Render();
}
