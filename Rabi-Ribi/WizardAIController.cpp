#include "WizardAIController.h"
#include "Wizard.h"

WizardAIController::WizardAIController()
{
}

WizardAIController::~WizardAIController()
{
}

HRESULT WizardAIController::Init()
{
	return S_OK;
}

void WizardAIController::Release()
{
	Super::Release();
}

void WizardAIController::Update()
{
	AIBase::Update();
	if (taget)
	{
		Actor* a_taget = Cast<Actor>(taget);
		Vector2_F tagetLocation = a_taget->GetLocation();
		Vector2_F ownerLocation = Cast<Actor>(owner)->GetLocation();
		Vector2_F moveLocation = ownerLocation - tagetLocation;
		if (moveLocation.x < 0.0f)
		{
			moveLocation.x += 70.0f;
			if (moveLocation.x > 0.0f)
				moveLocation.x = 0.0f;
			
		}
		else
		{
			moveLocation.x -= 70.0f;
			if (moveLocation.x < 0.0f)
				moveLocation.x = 0.0f;
			
		}
		Wizard* wizard = Cast<Wizard>(owner); 
		if (wizard->GetAnimKinds() == AnimationKinds::Attack1)
			return;
		wizard->MoveCharacter(moveLocation);
		taget = nullptr;
		if (moveLocation.x == 0.0f)
		{
			wizard->SetAnimKinds(AnimationKinds::Attack1);
			wizard->SetMoveLock(true);
		}

	}
	else
	{
		float randomValue = ((float)(rand() % 500) * 0.1f) - 25.0f;
		Vector2_F moveLocation(0.0f, 0.0f);
		Cast<Enemy>(owner)->MoveCharacter(moveLocation);
	}
}

void WizardAIController::Render()
{
	Super::Render();
}
