#include "WizardAnimInstance.h"
#include "Animation.h"
#include "Wizard.h"

WizardAnimInstance::WizardAnimInstance()
{
	// Blue
	Animation* nowAnim = new Animation;
	nowAnim->Setting({ 0,0 }, { 3,0 }, 0.15f);
	animations.insert(make_pair("Idle_b", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,1 }, { 4, 1 }, 0.15f);
	animations.insert(make_pair("Move_b", nowAnim));
	
	nowAnim = new Animation;
	nowAnim->Setting({ 0,2 }, { 3, 2 }, 0.10f);
	animations.insert(make_pair("Jum_b", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,3 }, { 3, 3 }, 0.10f);
	nowAnim->SettingLoopIndex({ 1,3 }, {3,3});
	animations.insert(make_pair("Falling_b", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 0,4 }, { 4, 4 }, 0.10f);
	nowAnim->SettingLoopIndex({ 2,4 }, { 4, 4 });
	animations.insert(make_pair("Attack_b", nowAnim));

	nowAnim = new Animation;
	nowAnim->Setting({ 4,0 }, { 4,0 }, 0.10f);
	animations.insert(make_pair("Hit_b", nowAnim));

	// Red
	nowAnim = new Animation;
	nowAnim->Setting({ 5,0}, { 8, 0 }, 0.10f);
	animations.insert(make_pair("Idle_r", nowAnim));


	// Green
	nowAnim = new Animation;
	nowAnim->Setting({ 0,5 }, { 3,5 }, 0.10f);
	animations.insert(make_pair("Idle_g", nowAnim));


	// yellow
	nowAnim = new Animation;
	nowAnim->Setting({ 5,5 }, { 5,8 }, 0.10f);
	animations.insert(make_pair("Idle_y", nowAnim));
}

WizardAnimInstance::~WizardAnimInstance()
{
}

HRESULT WizardAnimInstance::Init()
{
	return S_OK;
}

void WizardAnimInstance::Release()
{
	Super::Release();
}

void WizardAnimInstance::Update()
{
	Super::Update();
	Wizard* wizard = Cast<Wizard>(owner);
	string animKeyValue = "";
	if (wizard == nullptr)
		return;
	Location ownerLocation = wizard->GetLocation();
	switch (wizard->GetAnimKinds())
	{
	case AnimationKinds::Idle:
		animKeyValue = "Idle" + suffix[(int)(wizard->GetWizardType())];
		PlayingAnimation(animKeyValue);
		break;
	case AnimationKinds::Move_Right:
	case AnimationKinds::Move_Left:
		animKeyValue = "Move" + suffix[(int)(wizard->GetWizardType())];
		PlayingAnimation(animKeyValue);
		break;
	case AnimationKinds::Jump:
		animKeyValue = "Jum" + suffix[(int)(wizard->GetWizardType())];
		PlayingAnimation(animKeyValue);
		break;
	case AnimationKinds::Falling:
		animKeyValue = "Falling" + suffix[(int)(wizard->GetWizardType())];
		PlayingAnimation(animKeyValue);
		break;
	case AnimationKinds::Hit:
		animKeyValue = "Hit" + suffix[(int)(wizard->GetWizardType())];
		PlayingAnimation(animKeyValue);
		break;
	case AnimationKinds::Attack1:
	case AnimationKinds::Attack2:
	case AnimationKinds::Attack3:
	case AnimationKinds::Attack4:
		animKeyValue = "Attack" + suffix[(int)(wizard->GetWizardType())];
		PlayingAnimation(animKeyValue);
		wizard->Attack();
		break;
	default:
		animKeyValue = "Idle" + suffix[(int)(wizard->GetWizardType())];
		PlayingAnimation(animKeyValue);
		break;
	}
}

void WizardAnimInstance::Render()
{
	Super::Render();
}
