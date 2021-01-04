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
		Vector2_F moveLocation = ownerLocation - tagetLocation;

		Cast<Enemy>(owner)->MoveCharacter(moveLocation);
		taget = nullptr;

	}
	else
	{
		Vector2_F moveLocation( 0.0f,0.0f );
		Cast<Enemy>(owner)->MoveCharacter(moveLocation);
	}
	
}

void EnemyAIController::Render()
{
	Super::Render();
}
