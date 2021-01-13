#include "ErinaAnimInstance.h"
#include "Animation.h"
#include "Erina.h"
#include "Hammer.h"
#include "HammerAnimInstance.h"

ErinaAnimInstance::ErinaAnimInstance()
{
	// 
	Animation* IdleAnim = new Animation;
	IdleAnim->Setting({ 0,0 }, {7,0},0.10f);
	animations.insert(make_pair("Idle", IdleAnim));

	Animation* LeftAnim = new Animation;
	LeftAnim->Setting({ 0,1 }, { 5,1 }, 0.10f);
	animations.insert(make_pair("Left", LeftAnim));

	Animation* RightAnim = new Animation;
	RightAnim->Setting({ 0,1 }, { 5,1 }, 0.10f, true);
	animations.insert(make_pair("Right", RightAnim));

	Animation* JumAnim = new Animation;
	JumAnim->Setting({ 0,2 }, { 3,2 }, 0.10f,false);
	animations.insert(make_pair("Jum", JumAnim));

	Animation* DoubleJumAnim = new Animation;
	DoubleJumAnim->Setting({ 0,3 }, { 5,3 }, 0.07f, false);
	animations.insert(make_pair("DoubleJumAnim", DoubleJumAnim));

	Animation* FallingAnim = new Animation;
	FallingAnim->Setting({ 0,4 }, { 3,4 }, 0.10f);
	FallingAnim->SettingLoopIndex({ 1,4 }, { 3,4 });
	animations.insert(make_pair("Falling", FallingAnim));

	Animation* Attack1Anim = new Animation;
	Attack1Anim->Setting({ 0,10 }, { 5,10 }, 0.05f , false);
	animations.insert(make_pair("Attack1", Attack1Anim));

	Animation* Attack2Anim = new Animation;
	Attack2Anim->Setting({ 0,11 }, { 6,11 }, 0.04f, false);
	animations.insert(make_pair("Attack2", Attack2Anim));

	Animation* Attack3Anim = new Animation;
	Attack3Anim->Setting({ 0,7 }, { 9,7 }, 0.05f, false);
	animations.insert(make_pair("Attack3", Attack3Anim));

	Animation* HitAnim = new Animation;
	HitAnim->Setting({ 0,8 }, { 1,8 }, 0.10f, false);
	animations.insert(make_pair("Hit", HitAnim));

	Animation* CrrotBoomChargeAnim = new Animation;
	CrrotBoomChargeAnim->Setting({ 0,6 }, { 2,6 }, 0.10f, false);
	animations.insert(make_pair("CrrotBoomChargeAnim", CrrotBoomChargeAnim));

	Animation* CrrotBoomAnim = new Animation;
	CrrotBoomAnim->Setting({ 3,6 }, { 9,6 }, 0.10f, false);
	animations.insert(make_pair("CrrotBoomAnim", CrrotBoomAnim));

	Animation* SlidingAnim = new Animation;
	SlidingAnim->Setting({ 0,5 }, { 3,5 }, 0.10f);
	SlidingAnim->SettingLoopIndex({ 1,5 }, { 3,5 });
	animations.insert(make_pair("SlidingAnim", SlidingAnim));
}

ErinaAnimInstance::~ErinaAnimInstance()
{
}

HRESULT ErinaAnimInstance::Init()
{
	return S_OK;
}

void ErinaAnimInstance::Release()
{
	SafemapRelease(animations);
}

void ErinaAnimInstance::Update()
{
	if (owner == nullptr)
		return;
	Erina* erina = Cast<Erina>(owner);

	switch (erina->GetAnimKinds())
	{
	default:
	case AnimationKinds::Idle:
		PlayingAnimation("Idle");
		break;
	case AnimationKinds::Move_Right:
		PlayingAnimation("Right");
		break;
	case AnimationKinds::Move_Left:
		PlayingAnimation("Left");
		break;
	case AnimationKinds::Jump:
		PlayingAnimation("Jum");
		if (playingAnimation->IsEnd())
			erina->SetAnimKinds(AnimationKinds::Falling);
		break;
	case AnimationKinds::DoubleJum:
		PlayingAnimation("DoubleJumAnim");
		if (playingAnimation->IsEnd())
			erina->SetAnimKinds(AnimationKinds::Falling);
		break;
	case AnimationKinds::Hit:
		PlayingAnimation("Hit");
		break;
	case AnimationKinds::Falling:
		PlayingAnimation("Falling");
		break;
	case AnimationKinds::Attack1:
		PlayingAnimation("Attack1");
		//if (playingAnimation->IsEnd())
		{
			erina->GetPikoHammer()->SetIsValid(true);
			erina->GetPikoHammer()->SetAnimationKinds(HammerAnimationKinds::Attack_1);
			if ((playingAnimation->IsEnd()) & (erina->GetNextAttack()))
			{
				erina->SetAnimKinds(AnimationKinds::Attack2);
			}
		}
		break;
	case AnimationKinds::Attack2:
		PlayingAnimation("Attack2");
		//if (playingAnimation->IsEnd())
		{
			erina->GetPikoHammer()->SetIsValid(true);
			erina->GetPikoHammer()->SetAnimationKinds(HammerAnimationKinds::Attack_2);
			if ((playingAnimation->IsEnd()) & (erina->GetNextAttack()))
			{
				erina->SetAnimKinds(AnimationKinds::Attack3);
			}
		}
		break;
	case AnimationKinds::Attack3:
		PlayingAnimation("Attack3");
		//if (playingAnimation->IsEnd())
		{
			erina->GetPikoHammer()->SetIsValid(true);
			erina->GetPikoHammer()->SetAnimationKinds(HammerAnimationKinds::Attack_3);
			if ((playingAnimation->IsEnd()) & (erina->GetNextAttack()))
			{
				erina->SetAnimKinds(AnimationKinds::Attack4);
			}
		}
		break;
	case AnimationKinds::Attack4:
		PlayingAnimation("Attack1");
		erina->GetPikoHammer()->SetAnimationKinds(HammerAnimationKinds::Attack_4);
		if (playingAnimation->IsEnd())
		{
			erina->GetPikoHammer()->SetAnimationKinds(HammerAnimationKinds::None);
			erina->SetMoveLock(false);
			erina->SetNextAttack(false);
			erina->SetAnimKinds(AnimationKinds::Idle);
		}
		break;
	case AnimationKinds::BombCharge:
		PlayingAnimation("CrrotBoomChargeAnim");
		break;
	case AnimationKinds::Bomb:
		PlayingAnimation("CrrotBoomAnim");
		if (playingAnimation->IsEnd())
			erina->SetMoveLock(false);
		break;
	case AnimationKinds::Sliding:
		PlayingAnimation("SlidingAnim");
		break;
	}
}

void ErinaAnimInstance::Render()
{
	Super::Render();
}
