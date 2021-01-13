#include "CocoaAIController.h"
#include "Cocoa.h"
#include "PlayScene.h"
#include "BlackBomb.h"
#include "ProjectileManager.h"
#include "Projectile.h"

CocoaAIController::CocoaAIController()
{
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
