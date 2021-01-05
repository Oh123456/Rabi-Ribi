#include "RebbonAnimInstance.h"
#include "Animation.h"
#include "Rebbon.h"
#include "Rebbon_Weapon.h"

RebbonAnimInstance::RebbonAnimInstance()
{
	Animation* IdleAnim = new Animation;
	IdleAnim->Setting({ 1,0 }, { 4, 0 }, 0.07f);
	animations.insert(make_pair("Idle", IdleAnim));
}

RebbonAnimInstance::~RebbonAnimInstance()
{
}

HRESULT RebbonAnimInstance::Init()
{
	return S_OK;
}

void RebbonAnimInstance::Release()
{
	Super::Release();
}

void RebbonAnimInstance::Update()
{
	Super::Update();
	ObjectBase* objectbase = Cast<ObjectBase>(owner);
	Rebbon* rebbon = Cast<Rebbon>(objectbase);
	if (rebbon)
	{
		switch (rebbon->GetAinimationKinds())
		{
		case RebbonAnimationKinds::Idle:
			PlayingAnimation("Idle");
			break;
		default:
			break;
		}
	}
}

void RebbonAnimInstance::Render()
{
	Super::Render();
}
