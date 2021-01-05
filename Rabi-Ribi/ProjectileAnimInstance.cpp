#include "ProjectileAnimInstance.h"
#include "Projectile.h"
#include "Animation.h"

#define AnimDelelyTime 0.05f
ProjectileAnimInstance::ProjectileAnimInstance()
{
	Animation* C_Red = new Animation;
	C_Red->Setting({ 0,0 }, { 0,6 }, AnimDelelyTime);
	animations.insert(make_pair("Circle_Red", C_Red));

	Animation* C_Blue = new Animation;
	C_Blue->Setting({ 1,0 }, { 1,6 }, AnimDelelyTime, false);
	animations.insert(make_pair("Circle_Blue", C_Blue));

	Animation* C_Purple = new Animation;
	C_Purple->Setting({ 6,0 }, { 6,6 }, AnimDelelyTime, false);
	animations.insert(make_pair("Circle_Purple", C_Purple));

	Animation* C_Green = new Animation;
	C_Green->Setting({ 7,0 }, { 7,6 }, AnimDelelyTime, false);
	animations.insert(make_pair("Circle_Green", C_Green));

}

ProjectileAnimInstance::~ProjectileAnimInstance()
{
}

HRESULT ProjectileAnimInstance::Init()
{
	return S_OK;
}

void ProjectileAnimInstance::Release()
{
	Super::Release();
}

void ProjectileAnimInstance::Update()
{
	Super::Update();
	Projectile* porjectile = Cast<Projectile>(owner);
	switch (porjectile->GetProjectileAnimationKinds())
	{
	case ProjectileAnimationKinds::Circle_Red:
		PlayingAnimation("Circle_Red");
		break;
	case ProjectileAnimationKinds::Circle_Blue:
		PlayingAnimation("Circle_Blue");
		break;
	case ProjectileAnimationKinds::Circle_Green:
		PlayingAnimation("Circle_Green");
		break;
	case ProjectileAnimationKinds::Circle_Purple:
		PlayingAnimation("Circle_Purple");
		break;
	case ProjectileAnimationKinds::Missile_Blue:
		break;
	case ProjectileAnimationKinds::Missile_Red:
		break;
	case ProjectileAnimationKinds::Missile_Green:
		break;
	default:
		break;
	}
}

void ProjectileAnimInstance::Render()
{
	Super::Render();
}
