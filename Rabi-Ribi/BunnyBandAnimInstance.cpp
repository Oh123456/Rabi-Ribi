#include "BunnyBandAnimInstance.h"
#include "Animation.h"
#include "BunnyBand.h"

BunnyBandAnimInstance::BunnyBandAnimInstance()
{
	Animation* nowAnim = new Animation;
	nowAnim->Setting({ 0,0 }, { 3,0 }, 0.15f);
	bunnyBandAnimations.insert(make_pair("Idle", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,1 }, { 4, 1 }, 0.15f);
	bunnyBandAnimations.insert(make_pair("Move", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,2 }, { 2, 2 }, 0.10f);
	bunnyBandAnimations.insert(make_pair("Jum", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,3 }, { 2, 3 }, 0.10f);
	bunnyBandAnimations.insert(make_pair("Falling", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,4 }, { 4, 4 }, 0.10f, false);
	bunnyBandAnimations.insert(make_pair("Attack", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 4,0 }, { 4,0 }, 0.10f);
	bunnyBandAnimations.insert(make_pair("Hit", nowAnim));
}

BunnyBandAnimInstance::~BunnyBandAnimInstance()
{
}

HRESULT BunnyBandAnimInstance::Init()
{
	return S_OK;
}

void BunnyBandAnimInstance::Release()
{
	Super::Release();
	SafemapRelease(bunnyBandAnimations);
}

void BunnyBandAnimInstance::Update()
{
	Super::Update();
	BunnyBand* bunnyBand = Cast<BunnyBand>(owner);
	if (bunnyBand)
	{
		switch (bunnyBand->GetAnimKinds())
		{
		case AnimationKinds::Idle:
			PlayingBunnyBandAnimation("Idle");
			break;
		case AnimationKinds::Move_Right:
			PlayingBunnyBandAnimation("Idle");
			if (bunnyBandimageInfo->affineMatrix.m11 > 0.0f)
				bunnyBandimageInfo->affineMatrix.m11 *= -1.0f;
		case AnimationKinds::Move_Left:
			PlayingBunnyBandAnimation("Idle");
			if (bunnyBandimageInfo->affineMatrix.m11 < 0.0f)
				bunnyBandimageInfo->affineMatrix.m11 *= -1.0f;
			break;
		case AnimationKinds::Jump:
			PlayingBunnyBandAnimation("Jum");
			break;
		case AnimationKinds::Falling:
			PlayingBunnyBandAnimation("Falling");
			break;
		case AnimationKinds::Hit:
			PlayingBunnyBandAnimation("Hit");
			break;
		case AnimationKinds::Attack1:
		case AnimationKinds::Attack2:	
		case AnimationKinds::Attack3:
		case AnimationKinds::Attack4:
			PlayingBunnyBandAnimation("Attack");
			break;
		default:
			break;
		}
	}
}

void BunnyBandAnimInstance::Render()
{
	Super::Render();
	if (playingBunnyBandAnimation)
		playingBunnyBandAnimation->Render(bunnyBandimageInfo);
}

void BunnyBandAnimInstance::SetOwner(Actor* owner)
{
	Super::SetOwner(owner);
	BunnyBand* bunnyBand = Cast<BunnyBand>(owner);

	if (bunnyBand)
		bunnyBandimageInfo = bunnyBand->GetBunnyBandImageInfo_ptr();
	
}

void BunnyBandAnimInstance::ChangeBunnyBandAnimation(IAnimation * findAnim)
{
	map<string, struct IAnimation*>::const_iterator c_it;
	for (c_it = bunnyBandAnimations.begin(); c_it != bunnyBandAnimations.end(); c_it++)
	{
		if (c_it->second != findAnim)
			c_it->second->Stop();
	}
}

void BunnyBandAnimInstance::PlayingBunnyBandAnimation(string animkeyValue)
{
	IAnimation* anim = bunnyBandAnimations.find(animkeyValue)->second;
	ChangeBunnyBandAnimation(anim);
	if (!anim->IsPlaying())
	{
		anim->Play();
		playingBunnyBandAnimation = anim;
	}
}
