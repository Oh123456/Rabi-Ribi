#include "ProjectileManager.h"
#include "Projectile.h"
#include "CarrotBomb.h"
#include "BlackBomb.h"

ProjectileManager::ProjectileManager()
{
}

ProjectileManager::~ProjectileManager()
{
}

HRESULT ProjectileManager::Init()
{
	for (int i = 0; i < 200; i++)
	{
		Projectile* projectile = CreateObject<Projectile>();// ->SetIsValid(true);
		projectile->SetIsValid(false);
		projectiles.push_back(projectile);
	}

	carrotBomb = CreateObject<CarrotBomb>();
	carrotBomb->SetIsValid(false);
	return S_OK;
}

void ProjectileManager::Release()
{
	Super::Release();
}

void ProjectileManager::Update()
{
	Super::Update();

	list <class Projectile*>::const_iterator c_it;
	for (c_it = activeProjectiles.begin(); c_it != activeProjectiles.end();)
	{
		if (!(*c_it)->GetIsValid())
		{
			projectiles.push_back(*c_it);
			c_it = activeProjectiles.erase(c_it);
		}
		else
			c_it++;
	}
}

void ProjectileManager::Render()
{
	Super::Render();
}

Projectile * ProjectileManager::SpawnProjectile()
{
	if (projectiles.empty())
	{
		Projectile* projectile = CreateObject<Projectile>();
		projectiles.push_back(projectile);
		return projectile;
	}
	Projectile* projectile = projectiles.front();
	projectiles.pop_front();

	activeProjectiles.push_back(projectile);
	return projectile;
}

Projectile * ProjectileManager::SpawnCarrotBomb()
{
	if (carrotBomb->GetIsValid())
		return nullptr;
	carrotBomb->SetIsValid(true);
	return carrotBomb;
}
