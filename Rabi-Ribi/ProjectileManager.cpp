#include "ProjectileManager.h"
#include "Projectile.h"

ProjectileManager::ProjectileManager()
{
	isNotUPdate = true;
}

ProjectileManager::~ProjectileManager()
{
}

HRESULT ProjectileManager::Init()
{
	for (int i = 0; i < 50; i++)
		CreateObject<Projectile>()->SetIsValid(true);
	return S_OK;
}

void ProjectileManager::Release()
{
}

void ProjectileManager::Update()
{
}

void ProjectileManager::Render()
{
	Super::Render();
}
