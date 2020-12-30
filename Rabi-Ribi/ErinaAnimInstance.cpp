#include "ErinaAnimInstance.h"
#include "Animation.h"
#include "Erina.h"

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

	Animation* FallingAnim = new Animation;
	FallingAnim->Setting({ 0,4 }, { 3,4 }, 0.10f);
	FallingAnim->SettingLoopIndex({ 1,4 }, { 3,4 });
	animations.insert(make_pair("Falling", FallingAnim));
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
	case AnimmationKinds::Idle:
		PlayingAnimation("Idle");
		break;
	case AnimmationKinds::Move_Right:
		PlayingAnimation("Right");
		break;
	case AnimmationKinds::Move_Left:
		PlayingAnimation("Left");
		break;
	case AnimmationKinds::Jum:
		PlayingAnimation("Jum");
		if (playingAnimation->IsEnd())
			erina->SetAnimKinds(AnimmationKinds::Falling);
		break;
	case AnimmationKinds::Falling:
		PlayingAnimation("Falling");
		break;
	}
}

void ErinaAnimInstance::Render()
{
	Super::Render();
}
