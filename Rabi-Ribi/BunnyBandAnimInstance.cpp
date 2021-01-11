#include "BunnyBandAnimInstance.h"
#include "Animation.h"

BunnyBandAnimInstance::BunnyBandAnimInstance()
{
	Animation* nowAnim = new Animation;
	nowAnim->Setting({ 0,0 }, { 4,0 }, 0.15f);
	animations.insert(make_pair("Idle", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,1 }, { 4, 1 }, 0.15f);
	animations.insert(make_pair("Move", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,2 }, { 2, 2 }, 0.10f);
	animations.insert(make_pair("Jum", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,3 }, { 2, 3 }, 0.10f);
	animations.insert(make_pair("Falling", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,4 }, { 4, 4 }, 0.10f);
	nowAnim->SettingLoopIndex({ 2,4 }, { 4, 4 });
	animations.insert(make_pair("Attack", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 4,0 }, { 4,0 }, 0.10f);
	animations.insert(make_pair("Hit", nowAnim));
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
}

void BunnyBandAnimInstance::Update()
{
	Super::Update();

}

void BunnyBandAnimInstance::Render()
{
	Super::Render();
}
