#include "ProjectileManager.h"
#include "Projectile.h"

ProjectileManager::ProjectileManager()
{
}

ProjectileManager::~ProjectileManager()
{
}

HRESULT ProjectileManager::Init()
{
	for (int i = 0; i < 50; i++)
	{
		Projectile* projectile = CreateObject<Projectile>();// ->SetIsValid(true);
		//projectile->SetIsValid(true);
		projectiles.push_back(projectile);
	}
	return S_OK;
}

void ProjectileManager::Release()
{
	Super::Release();
}

void ProjectileManager::Update()
{
	Super::Update();
}

void ProjectileManager::Render()
{
	Super::Render();
}
