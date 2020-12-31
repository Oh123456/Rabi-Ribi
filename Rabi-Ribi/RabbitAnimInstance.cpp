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
	HitAnim->Setting({ 1,1 }, { 1,1 }, 0.10f);
	animations.insert(make_pair("Hit", HitAnim));

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
	case AnimmationKinds::Idle:
		PlayingAnimation("Idle");
		break;
	case AnimmationKinds::Move_Right:
	case AnimmationKinds::Move_Left:
		PlayingAnimation("Move");
		break;
	case AnimmationKinds::Hit:
		PlayingAnimation("Hit");
		break;
	case AnimmationKinds::Jum:
		break;
	case AnimmationKinds::Falling:
		break;
	case AnimmationKinds::Attack1:
		break;
	case AnimmationKinds::Attack2:
		break;
	case AnimmationKinds::Attack3:
		break;
	case AnimmationKinds::Attack4:
		break;
	default:
		break;
	}
}

void RabbitAnimInstance::Render()
{
	Super::Render();
}
