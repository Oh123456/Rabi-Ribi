#include "CocoaAIController.h"
#include "Cocoa.h"

CocoaAIController::CocoaAIController()
{
}

CocoaAIController::~CocoaAIController()
{
}

HRESULT CocoaAIController::Init()
{
	jumptest = false;
	return S_OK;
}

void CocoaAIController::Release()
{
	Super::Release();
}

void CocoaAIController::Update()
{
	Super::Update();
	
	if (KEYMANAGER->IsOnceKeyDown(VK_HOME))
		jumptest = true;
	if (jumptest)
		BackJumpMove();
}

void CocoaAIController::Render()
{
	Super::Render();
}

void CocoaAIController::BackJumpMove()
{
	static float test = 0.0f;
	Super::Update();
	Cocoa* cocoa = Cast<Cocoa>(owner);
	test += TIMERMANAGER->GetTimeElapsed();
	if (test <= 0.15f)
	{
		cocoa->Jump();
		if (cocoa->GetAnimKinds() != AnimationKinds::Hit)
			cocoa->SetAnimKinds(AnimationKinds::Jump);
	}
	if (cocoa->GetAnimKinds() == AnimationKinds::Idle)
	{
		jumptest = false;
		test = 0.0f;
	}
	else
	{
		if (cocoa->GetImageInfo_ptr()->affineMatrix.m11 > 0.0f)
			cocoa->MoveCharacter({ -2.0f,2.0f });
		else
			cocoa->MoveCharacter({ 2.0f,2.0f });
	}
}
