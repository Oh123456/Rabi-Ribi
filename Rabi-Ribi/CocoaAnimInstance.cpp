#include "CocoaAnimInstance.h"
#include "Animation.h"
#include "Cocoa.h"

CocoaAnimInstance::CocoaAnimInstance()
{
	Animation* nowAnim = new Animation;
	nowAnim->Setting({ 0,0 }, { 3,0 }, 0.15f);
	animations.insert(make_pair("Idle", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,1 }, { 5, 1 }, 0.15f);
	animations.insert(make_pair("Move", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,2 }, { 3, 2 }, 0.10f);
	animations.insert(make_pair("Jum", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,4 }, { 3, 4 }, 0.10f);
	animations.insert(make_pair("Falling", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,3 }, { 4, 3 }, 0.10f, false);
	animations.insert(make_pair("Attack", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,6 }, { 3, 6 }, 0.10f);
	nowAnim->SettingLoopIndex({1 ,6 }, { 3, 6 });
	animations.insert(make_pair("Attack2", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 4,6 }, { 5,6 }, 0.10f);
	animations.insert(make_pair("Hit", nowAnim));
}

CocoaAnimInstance::~CocoaAnimInstance()
{
}

HRESULT CocoaAnimInstance::Init()
{
	return S_OK;
}

void CocoaAnimInstance::Release()
{
	Super::Release();
}

void CocoaAnimInstance::Update()
{
	Super::Update(); 
	Cocoa* cocoa = Cast<Cocoa>(owner);
	switch (cocoa->GetAnimKinds())
	{
	case AnimationKinds::Idle:
		PlayingAnimation("Idle");
		break;
	case AnimationKinds::Move_Right:
	case AnimationKinds::Move_Left:
		PlayingAnimation("Move");
		break;
	case AnimationKinds::Jump:
		PlayingAnimation("Jum");
		break;
	case AnimationKinds::Falling:
		PlayingAnimation("Falling");
		break;
	case AnimationKinds::Hit:
		PlayingAnimation("Hit");
		break;
	case AnimationKinds::Attack1:
		PlayingAnimation("Attack1");
		break;
	case AnimationKinds::Attack2:
		PlayingAnimation("Attack2");
		cocoa->SetNoAnimChange(true);
		//if (playingAnimation->IsEnd())
		{
			if (!TIMERMANAGER->ExistTimer(timer))
			{
				TIMERMANAGER->SetTimer(timer, this, &CocoaAnimInstance::AnimationEnd);
				cocoa->CallCatHelicoter();
			}
			
		}
		break;
	case AnimationKinds::Attack3:
		PlayingAnimation("Attack2");
		cocoa->SetNoAnimChange(true);
		//if (playingAnimation->IsEnd())
		{
			if (!TIMERMANAGER->ExistTimer(timer))
			{
				TIMERMANAGER->SetTimer(timer, this, &CocoaAnimInstance::AnimationEnd);
				cocoa->CallTwoCatHelicoter();
			}

		}
		break;
	case AnimationKinds::Attack4:
		break;
	default:
		break;
	}
}

void CocoaAnimInstance::Render()
{
	Super::Render();
}

void CocoaAnimInstance::AnimationEnd()
{
	Cocoa* cocoa = Cast<Cocoa>(owner);
	cocoa->SetNoAnimChange(false);
	cocoa->SetAnimKinds(AnimationKinds::Idle);
	TIMERMANAGER->DeleteTimer(timer);
}
