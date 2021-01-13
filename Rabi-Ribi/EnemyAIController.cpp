#include "EnemyAIController.h"
#include "Erina.h"
#include "Enemy.h"

EnemyAIController::EnemyAIController() :
	taget(nullptr)
{
}

EnemyAIController::~EnemyAIController()
{
}

HRESULT EnemyAIController::Init()
{
	return S_OK;
}

void EnemyAIController::Release()
{
	Super::Release();
}

void EnemyAIController::Update()
{
	Super::Update();
	if (taget)
	{
		Actor* a_taget = Cast<Actor>(taget);
		Vector2_F tagetLocation = a_taget->GetLocation();
		Vector2_F ownerLocation = Cast<Actor>(owner)->GetLocation();
		moveLocation = ownerLocation - tagetLocation;

		Cast<Enemy>(owner)->MoveCharacter(moveLocation);
		taget = nullptr;

	}
	else
	{
		if (isMoveLocation)
		{
			Vector2_F ownerLocation = Cast<Actor>(owner)->GetWorldLocation();
			Vector2_F moveLocation = ownerLocation - this->moveLocation;
			Cast<Enemy>(owner)->MoveCharacter(moveLocation);
		}

		else
		{
			moveLocation = { 0.0f, 0.0f };
			Cast<Enemy>(owner)->MoveCharacter(moveLocation);
		}
	}
	
}

void EnemyAIController::Render()
{
	Super::Render();
}

void EnemyAIController::MoveToLocation(Vector2_F location)
{
	isMoveLocation = true;
	moveLocation = location;
}
