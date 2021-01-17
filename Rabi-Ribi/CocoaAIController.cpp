#include "CocoaAIController.h"
#include "Cocoa.h"
#include "PlayScene.h"
#include "BlackBomb.h"
#include "ProjectileManager.h"
#include "Projectile.h"
#include "CatHelicopter.h"

CocoaAIController::CocoaAIController()
{
	TIMERMANAGER->SetTimer(pattenTimer,this, &CocoaAIController::Patten , 1.8f);
}

CocoaAIController::~CocoaAIController()
{
}

HRESULT CocoaAIController::Init()
{
	jumpCheck = false;
	PlayScene* playScene = Cast<PlayScene>(SceneManager::currScene);
	if (playScene)
		taget = playScene->GetPlayer();
	jumpDelayTime = 0.15f;
	jumpTime = 0.0f;
	return S_OK;
}

void CocoaAIController::Release()
{
	Super::Release();
}

void CocoaAIController::Update()
{
	if (isMoveLocation)
	{
		

		Vector2_F ownerLocation = Cast<Actor>(owner)->GetWorldLocation();
		Vector2_F moveLocation = ownerLocation - this->moveLocation;
		if (!Range_Included(-0.5f, moveLocation.x, 0.5f))
			Cast<Enemy>(owner)->MoveCharacter(moveLocation);
		else
			Cast<Enemy>(owner)->SetAnimKinds(AnimationKinds::Idle);
		
	}




	if (taget)
	{
		Vector2_F ownerLocation = Cast<Character>(owner)->GetLocation();
		Vector2_F tagetLocation = taget->GetLocation();

		Vector2_F vector =  ownerLocation - tagetLocation;
		if (vector.x > 0.0f)
			Cast<Character>(owner)->ChangeDirection(ActorDirection::left);
		else if (vector.x < 0.0f)
			Cast<Character>(owner)->ChangeDirection(ActorDirection::Right);
	}


	if (KEYMANAGER->IsOnceKeyDown(VKey))
	{
		Cocoa* cocoa = Cast<Cocoa>(owner);
		cocoa->SetAnimKinds(AnimationKinds::Attack2);
		cocoa->SetNoAnimChange(true);
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_HOME))
	{
		jumpDelayTime = 0.5f;
		
		// CreateObject<BlackBomb>()->SetWorldLocation(taget->GetWorldLocation());
		if (!jumpCheck)
		{
			//jumpDelayTime = (float)(rand() % 15) * 0.01f;
			Cocoa* cocoa = Cast<Cocoa>(owner);
			cocoa->SetBackJumpShot();
			//cocoa->BoomAttack();
			if (cocoa->GetImageInfo_ptr()->affineMatrix.m11 > 0.0f)
				jumpBackDirection = Left;
			else
				jumpBackDirection = Right;
		}
		jumpCheck = true;
	}
#ifdef _DEBUG
#endif // _DEBUG
	if (jumpCheck)
		BackJumpShot(); 
}

void CocoaAIController::Render()
{
	Super::Render();
}

JumpStat CocoaAIController::BackJumpMove()
{
	Super::Update();
	JumpStat stat = JumpStat::Jump;
	Cocoa* cocoa = Cast<Cocoa>(owner);
	jumpTime += TIMERMANAGER->GetTimeElapsed();
	if (cocoa->GetAcceleration() >= 0.0f)
		stat = JumpStat::Faillng;
	if (jumpTime <= jumpDelayTime)
	{
		cocoa->Jump();
		if (cocoa->GetAnimKinds() != AnimationKinds::Hit)
			cocoa->SetAnimKinds(AnimationKinds::Jump);
		stat = JumpStat::Jump;
	}
	if ((cocoa->GetAnimKinds() != AnimationKinds::Jump) & (cocoa->GetAnimKinds() != AnimationKinds::Falling))
	{
		jumpCheck = false;
		jumpTime = 0.0f;
		stat = JumpStat::End;
	}
	else
	{
		if (jumpBackDirection == Left)
			cocoa->MoveCharacter({ -2.0f,2.0f });
		else
			cocoa->MoveCharacter({ 2.0f,2.0f });
	}
	return stat;
}


void CocoaAIController::BackJumpShot()
{
	JumpStat stat = BackJumpMove();
	Cocoa* cocoa = Cast<Cocoa>(owner);
	if (stat == JumpStat::Faillng)
		cocoa->onBackJumpShot.Execute();
}

void CocoaAIController::Patten()
{
	int randNum = rand() % 12;
	randNum = 8;
	Cocoa* cocoa = Cast<Cocoa>(owner);
	switch (randNum)
	{
	case 6:
	case 7:
	case 0:
		MoveToLocation( cocoa->MoveFont());
		//cocoa->SetAnimKinds(AnimationKinds::Idle);
		cocoa->SetNoAnimChange(true);
		jumpCheck = false;
		break;
	case 1:
		break;
	case 2:
		if ((cocoa->GetCatHelicopter()[0] != nullptr) | (cocoa->GetAnimKinds() == AnimationKinds::Falling))
			break;
		cocoa->SetAnimKinds(AnimationKinds::Attack3);
		cocoa->SetNoAnimChange(true);
		isMoveLocation = false;
		break;
	case 8:
	{
		float maxHP = (float)cocoa->GetMaxHP();
		float HP = (float)cocoa->GetHP();
		//if ((HP / maxHP) < 0.5f)
		{
			if ((cocoa->GetCatHelicopter()[0] == nullptr) & (cocoa->GetAnimKinds() != AnimationKinds::Falling))
			{
				cocoa->SetAnimKinds(AnimationKinds::Attack2);
				cocoa->SetNoAnimChange(true);
				isMoveLocation = false;
				break;
			}
				
		}
	}
	case 9:
		cocoa->BoomAttack();
		isMoveLocation = false;
	case 10:
	case 3:
		cocoa->SetNoAnimChange(false);
		if (!jumpCheck)
		{
			if (cocoa->GetImageInfo_ptr()->affineMatrix.m11 > 0.0f)
				jumpBackDirection = Left;
			else
				jumpBackDirection = Right;
			cocoa->Jump();
			jumpKinds = JumpKinds::BackJump;
		}
		jumpCheck = true;
		isMoveLocation = false;
		break;
	case 11:
	case 4:
		cocoa->SetNoAnimChange(false);
		jumpDelayTime = 0.5f;
		if (!jumpCheck)
		{
			cocoa->SetBackJumpShot();
			if (cocoa->GetImageInfo_ptr()->affineMatrix.m11 > 0.0f)
				jumpBackDirection = Left;
			else
				jumpBackDirection = Right;
			jumpKinds = JumpKinds::BackShotJum;
		}
		jumpCheck = true;
		isMoveLocation = false;
		break;
	default:
		break;
	}
}
