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
	RightAnim->Setting({ 0,1 }, { 5,1 }, 0.10f, true , true);
	animations.insert(make_pair("Right", RightAnim));
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
	if (ownerimageInfo == nullptr)
		ownerimageInfo = Cast<ImageInfo>(owner->GetImageInfo_ptr());
	Erina* erina = Cast<Erina>(owner);

	
	switch (erina->GetAnimKinds())
	{
	default:
	case ErinaAnimmationKinds::Idle:
		PlayingAnimation("Idle");
		break;
	case ErinaAnimmationKinds::Move_Right:
		PlayingAnimation("Right");
		break;
	case ErinaAnimmationKinds::Move_Left:
		PlayingAnimation("Left");
		break;
	}



}

void ErinaAnimInstance::Render()
{
	Super::Render();
}

void ErinaAnimInstance::ChangeAnimation(IAnimation* findAnim)
{
	map<string, struct IAnimation*>::const_iterator c_it;
	for (c_it = animations.begin(); c_it != animations.end(); c_it++)
	{
		if (c_it->second != findAnim)
			c_it->second->Stop();
	}
}

void ErinaAnimInstance::PlayingAnimation(string animkeyValue)
{
	IAnimation* anim = animations.find(animkeyValue)->second;
	ChangeAnimation(anim);
	if (!anim->IsPlaying())
	{
		anim->Play();
		playingAnimation = anim;
	}
}
