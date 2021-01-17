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
	for (int i = 0; i < 1600; i++)
	{
		Projectile* projectile = CreateObject<Projectile>();// ->SetIsValid(true);
		projectile->SetIsValid(false);
		projectiles.push_back(projectile);
	}

	Projectile* newCarrotBomb;
	for (int i = 0; i < 10; i++)
	{
		newCarrotBomb = CreateObject<CarrotBomb>();
		newCarrotBomb->SetIsValid(false);
		carrotBombs.push_back(newCarrotBomb);
	}
	for (int i = 0; i < 2; i++)
	{
		blackBomb[i] = CreateObject<BlackBomb>();
		blackBomb[i]->SetIsValid(false);
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

Projectile* ProjectileManager::SpawnCarrotBomb()
{
	Projectile* carrotBomb = carrotBombs.front();
	if (carrotBomb->GetIsValid())
		return nullptr;
	carrotBomb->SetIsValid(true);
	// 사용한것을 뒤로 넘겨 준다
	carrotBombs.push_back(carrotBomb);
	carrotBombs.pop_front();
	return carrotBomb;
}

Projectile** ProjectileManager::SpawnBlackBomb()
{
	if (blackBomb[0]->GetIsValid())
		return nullptr;
	else 
		return blackBomb;
}
