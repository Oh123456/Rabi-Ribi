#include "HammerAnimInstance.h"
#include "Hammer.h"
#include "Animation.h"

HammerAnimInstance::HammerAnimInstance()
{
	Animation* AttackAnim = new Animation;
	AttackAnim->Setting({ 0,0 }, { 7,0 }, 0.10f);
	animations.insert(make_pair("Idle", AttackAnim));
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

	switch (pikoHammer->GetAnimationKinds())
	{
	case HammerAnimationKinds::Attack_1:
		break;
	case HammerAnimationKinds::Attack_2:
		break;
	case HammerAnimationKinds::Attack_3:
		break;
	case HammerAnimationKinds::Attack_4:
		break;
	default:
		break;
	}

}

void HammerAnimInstance::Render()
{
	Super::Render();
}
