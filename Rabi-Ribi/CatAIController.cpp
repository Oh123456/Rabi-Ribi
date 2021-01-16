#include "CatAIController.h"
#include "PlayScene.h"
#include "Character.h"
#include "CatHelicopter.h"


CatAIController::CatAIController() : 
	attackCount(0), delay(0.0f) , isAttack(false) , isExit(false), exitCount(0) , nomalAttackspeed(1.0f)
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
	Object::Update();
	if (Cast<CatHelicopter>(owner)->GetCatHelicopterKinds() == CatHelicopterKinds::Pink)
	{
		if (taget)
		{
			Actor* a_taget = Cast<Actor>(taget);
			Vector2_F tagetLocation = a_taget->GetLocation();
			Vector2_F ownerLocation = Cast<Actor>(owner)->GetLocation();
			moveLocation = ownerLocation - tagetLocation;

			Cast<Enemy>(owner)->MoveCharacter({ moveLocation.x,0.0f });
			taget = nullptr;

		}
		else
		{
			if (exitCount >= 5)
				Cast<Enemy>(owner)->MoveCharacter(moveLocation);
			else if (isMoveLocation & !isAttack)
			{
				Vector2_F ownerLocation = Cast<Actor>(owner)->GetWorldLocation();
				Vector2_F moveLocation = ownerLocation - this->moveLocation;
				if ((Range_Included(-10.0f, moveLocation.x, 10.0f)) & (Range_Included(-10.0f, moveLocation.y, 10.0f)))
					isMoveLocation = false;
				Cast<Enemy>(owner)->MoveCharacter(moveLocation);
			}

			else
			{
				if (!isTagetMove)
				{
					if (isExit)
						owner->SetisActivation(false);
					else
					{
						Cast<CatHelicopter>(owner)->TagetMove();
						isTagetMove = true;
					}
				}
				else
				{
					delay += TIMERMANAGER->GetTimeElapsed();
					if (delay >= 1.0f)
					{
						isAttack = true;
						if (!TIMERMANAGER->ExistTimer(timer))
							TIMERMANAGER->SetTimer(timer, this, &CatAIController::TagetAttackDelay, 0.08f);
					}
				}
				//moveLocation = { 0.0f,0.0f };
				//Cast<Enemy>(owner)->MoveCharacter(moveLocation);
			}
		}
	}
	else
	{
		if (exitCount >= 8)
			Cast<Enemy>(owner)->MoveCharacter(moveLocation);
		if (isMoveLocation & !isAttack)
		{
			Vector2_F ownerLocation = Cast<Actor>(owner)->GetWorldLocation();
			Vector2_F moveLocation = ownerLocation - this->moveLocation;
			if ((Range_Included(-10.0f, moveLocation.x, 10.0f)) & (Range_Included(-10.0f, moveLocation.y, 10.0f)))
				isMoveLocation = false;
			Cast<Enemy>(owner)->MoveCharacter(moveLocation);
		}
		else 
			PattenMove();
	}
#ifdef _DEBUG
	if (KEYMANAGER->IsOnceKeyDown(_1Key))
	{
		PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
		MoveToLocation(playScene->GetPlayer()->GetWorldLocation());
	}
	if (KEYMANAGER->IsOnceKeyDown(_2Key))
	{
		TIMERMANAGER->SetTimer(timer,this,&CatAIController::AttackDelay, 0.03f);
	}
	if (KEYMANAGER->IsOnceKeyDown(_3Key))
	{
		TIMERMANAGER->SetTimer(timer, this, &CatAIController::TunMove_8AttackDelay, 0.03f);
	}
	if (KEYMANAGER->IsOnceKeyDown(_4Key))
	{
		TIMERMANAGER->SetTimer(timer, this, &CatAIController::TagetAttackDelay, 0.08f);
	}
#endif // _DEBUG
}

void CatAIController::Render()
{
}

void CatAIController::AttackDelay()
{
	CatHelicopter* cat = Cast<CatHelicopter>(owner);
	cat->TunMoveAttack();
	attackCount++;
	if (attackCount == 6)
	{
		attackCount = 0;
		TIMERMANAGER->DeleteTimer(timer);
		exitCount++;
		CatHelicopter* cat = Cast<CatHelicopter>(owner);
		MoveToLocation({ cat->GetWorldLocation().x + (40.0f * powf(-1.25f,(float)exitCount + 1.0f)) , cat->GetWorldLocation().y });
	}
}

void CatAIController::TunMove_8AttackDelay()
{
	CatHelicopter* cat = Cast<CatHelicopter>(owner);
	cat->TunMove_8Attack();
	//cat->TagetAttack();
	attackCount++;
	if (attackCount == 6)
	{
		attackCount = 0;
		TIMERMANAGER->DeleteTimer(timer);
		exitCount++;
		CatHelicopter* cat = Cast<CatHelicopter>(owner);
		MoveToLocation({ cat->GetWorldLocation().x + (40.0f * powf(-1.15f,(float)exitCount + 1.0f)) , cat->GetWorldLocation().y });
	}
}

void CatAIController::TagetAttackDelay()
{
	CatHelicopter* cat = Cast<CatHelicopter>(owner);
	//cat->TunMove_8Attack();
	cat->TagetAttack();
	attackCount++;
	if (attackCount == 10)
	{
		attackCount = 0;
		TIMERMANAGER->DeleteTimer(timer);
		isTagetMove = false;
		delay = 0.0f;
		isAttack = false;
		exitCount++;
	}
}

void CatAIController::PattenMove()
{
	delay += TIMERMANAGER->GetTimeElapsed();

	if (isExit)
		return;
	if (exitCount >= 8)
		CatAIController::Exit();
	if (exitCount >= 5)
	{
		CatHelicopter* cat = Cast<CatHelicopter>(owner);
		isMoveLocation = false;
		if (!TIMERMANAGER->ExistTimer(timer))
			TIMERMANAGER->SetTimer(timer, this, &CatAIController::TunMove_8AttackDelay, 0.03f);
	}
	else if (exitCount >= 3)
	{
		CatHelicopter* cat = Cast<CatHelicopter>(owner);
		isMoveLocation = false;
		if (!TIMERMANAGER->ExistTimer(timer))
			TIMERMANAGER->SetTimer(timer, this, &CatAIController::AttackDelay, 0.03f);
	}
	else
	{
		CatHelicopter* cat = Cast<CatHelicopter>(owner);
		MoveToLocation({ cat->GetWorldLocation().x + (40.0f * powf(-1.25f,(float)exitCount + 1.0f)) , cat->GetWorldLocation().y });
		cat->NomalAttack(nomalAttackspeed);
		nomalAttackspeed += 0.25f;
		exitCount++;
	}

	////if (delay >= 0.2f)
	//{
	//	if (!TIMERMANAGER->ExistTimer(timer))
	//		TIMERMANAGER->SetTimer(timer, this, &CatAIController::AttackDelay, 0.03f);
	//}
}

void CatAIController::Exit()
{
	MoveToLocation({ -20.f,-20.f });
	isExit = true;
}
