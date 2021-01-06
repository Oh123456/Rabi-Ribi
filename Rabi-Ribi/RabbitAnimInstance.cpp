#include "RabbitAnimInstance.h"
#include "Animation.h"
#include "Rabbit.h"


RabbitAnimInstance::RabbitAnimInstance()
{
	Animation* IdleAnim = new Animation;
	IdleAnim->Setting({ 0,0 }, { 0,2 }, 0.10f);
	animations.insert(make_pair("Idle", IdleAnim));

	Animation* MoveAnim = new Animation;
	MoveAnim->Setting({ 1,0 }, { 4,0 }, 0.10f);
	animations.insert(make_pair("Move", MoveAnim));

	Animation* HitAnim = new Animation;
	HitAnim->Setting({ 1,1 }, { 1,1 }, 0.10f, false);
	animations.insert(make_pair("Hit", HitAnim));
	 
	delayTime = 0.0f;
}

RabbitAnimInstance::~RabbitAnimInstance()
{
	
}

HRESULT RabbitAnimInstance::Init()
{
	return S_OK;
}

void RabbitAnimInstance::Release()
{
	Super::Release();
}

void RabbitAnimInstance::Update()
{
	if (owner == nullptr)
		return;
	Rabbit* rabbit = Cast<Rabbit>(owner);

	switch (rabbit->GetAnimKinds())
	{
	case AnimationKinds::Idle:
		PlayingAnimation("Idle");
		break;
	case AnimationKinds::Move_Right:
	case AnimationKinds::Move_Left:
		PlayingAnimation("Move");
		break;
	case AnimationKinds::Hit:
		PlayingAnimation("Hit");
		if (playingAnimation->IsEnd())
		{
			delayTime += TIMERMANAGER->GettimeElapsed();
			if (delayTime > 0.5f)
			{
				rabbit->SetAnimKinds(AnimationKinds::Idle);
				delayTime = 0.0f;
			}
		}
		break;
	case AnimationKinds::Jum:
	case AnimationKinds::Falling:
	case AnimationKinds::Attack1:
	case AnimationKinds::Attack2:
	case AnimationKinds::Attack3:
	case AnimationKinds::Attack4:
	default:
		delayTime = 0.0f;
		break;
	}
}

void RabbitAnimInstance::Render()
{
	Super::Render();
}
