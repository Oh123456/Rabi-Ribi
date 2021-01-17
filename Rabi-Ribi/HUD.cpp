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
	bossHPBar = nullptr;
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
		if (playScene->GetBoss())
		{
			if (bossHPBar == nullptr)
				bossHPBar = CreateObject<BossHPBar>();
			bossHPBar->BindCharacter(Cast<Character>(playScene->GetBoss()));
		}
	}


}

void HUD::Render()
{
	Super::Render();
}
