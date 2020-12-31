#include "HammerAnimInstance.h"
#include "Hammer.h"
#include "Animation.h"
#include "Erina.h"

HammerAnimInstance::HammerAnimInstance()
{
	Animation* AttackAnim = new Animation;
	AttackAnim->Setting({ 0,10 }, { 5,10 }, 0.05f,false);
	animations.insert(make_pair("Attack1", AttackAnim));

	Animation* Attack2Anim = new Animation;
	Attack2Anim->Setting({ 0,11 }, { 6,11 }, 0.05f, false);
	animations.insert(make_pair("Attack2", Attack2Anim));

	Animation* Attack3Anim = new Animation;
	Attack3Anim->Setting({ 0,0 }, { 9,0 }, 0.05f, false);
	animations.insert(make_pair("Attack3", Attack3Anim));

}

HammerAnimInstance::~HammerAnimInstance()
{
}

HRESULT HammerAnimInstance::Init()
{
	return S_OK;
}

void HammerAnimInstance::Release()
{
	Super::Release();
	SafemapRelease(animations);
}

void HammerAnimInstance::Update()
{
	Super::Update();
	if (owner == nullptr)
		return;
	Hammer* pikoHammer = Cast<Hammer>(owner);
	Erina* erina = Cast<Erina>(pikoHammer->GetOwner());
	const Location& erinaLocation = erina->GetLocation();
	ImageInfo* pikoHammerImageInfo = Cast<ImageInfo>(pikoHammer->GetImageInfo_ptr());
	switch (pikoHammer->GetAnimationKinds())
	{
	case HammerAnimationKinds::Attack_1:
		if (ownerimageInfo->affineMatrix.m11 > 0.0f)
			pikoHammer->SetLocation({ erinaLocation.x - 18.0f, erinaLocation.y - 2.0f });
		else 
			pikoHammer->SetLocation({ erinaLocation.x + 18.0f, erinaLocation.y - 2.0f });
		pikoHammerImageInfo->imageLocation = pikoHammer->GetLocation();
		PlayingAnimation("Attack1");
		if (playingAnimation->IsEnd())
		{
			if (!erina->GetNextAttack())
			{
				pikoHammer->SetAnimationKinds(HammerAnimationKinds::None);
				erina->SetMoveLock(false);
				erina->SetAnimKinds(AnimmationKinds::Idle);
			}
			else
			{
				pikoHammer->SetAnimationKinds(HammerAnimationKinds::Attack_2); 
				erina->SetNextAttack(false);
			}
		}
		break;
	case HammerAnimationKinds::Attack_2:
		pikoHammer->SetLocation({ erinaLocation.x , erinaLocation.y });
		pikoHammerImageInfo->imageLocation = pikoHammer->GetLocation();
		PlayingAnimation("Attack2");
		if (playingAnimation->IsEnd())
		{
			if (!erina->GetNextAttack())
			{
				pikoHammer->SetAnimationKinds(HammerAnimationKinds::None);
				erina->SetMoveLock(false);
				erina->SetAnimKinds(AnimmationKinds::Idle);
			}
			else
			{
				pikoHammer->SetAnimationKinds(HammerAnimationKinds::Attack_3);
				erina->SetNextAttack(false);
			}

		}
		break;
	case HammerAnimationKinds::Attack_3:
		pikoHammer->SetLocation({ erinaLocation.x, erinaLocation.y  });
		pikoHammerImageInfo->imageLocation = pikoHammer->GetLocation();
		PlayingAnimation("Attack3");
		if (playingAnimation->IsEnd())
		{
			if (!erina->GetNextAttack())
			{
				pikoHammer->SetAnimationKinds(HammerAnimationKinds::None);
				erina->SetMoveLock(false);
				erina->SetAnimKinds(AnimmationKinds::Idle);
			}
			else
			{
				pikoHammer->SetAnimationKinds(HammerAnimationKinds::Attack_4);
				erina->SetNextAttack(false);
			}
		}
		break;
	case HammerAnimationKinds::Attack_4:
		if (ownerimageInfo->affineMatrix.m11 > 0.0f)
			pikoHammer->SetLocation({ erinaLocation.x - 18.0f, erinaLocation.y - 2.0f });
		else
			pikoHammer->SetLocation({ erinaLocation.x + 18.0f, erinaLocation.y - 2.0f });
		pikoHammerImageInfo->imageLocation = pikoHammer->GetLocation();
		PlayingAnimation("Attack1");
		break;
	default:
		if (playingAnimation)
		{
			playingAnimation->Stop();
			playingAnimation = nullptr;
		}
		break;
	}

}

void HammerAnimInstance::Render()
{
	Super::Render();

}
