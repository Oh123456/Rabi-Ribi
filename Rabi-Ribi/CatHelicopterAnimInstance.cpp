#include "CatHelicopterAnimInstance.h"
#include "CatHelicopter.h"
#include "Animation.h"

CatHelicopterAnimInstance::CatHelicopterAnimInstance()
{
	Animation* newAnimation = new Animation;
	newAnimation->Setting({21, 5}, { 23, 5},0.1f);
	animations.insert(make_pair("Yellow", newAnimation));

	newAnimation = new Animation;
	newAnimation->Setting({ 26, 7 }, { 28, 7 }, 0.1f);
	animations.insert(make_pair("Pink", newAnimation));
}

CatHelicopterAnimInstance::~CatHelicopterAnimInstance()
{
}

HRESULT CatHelicopterAnimInstance::Init()
{
	return S_OK;
}

void CatHelicopterAnimInstance::Release()
{
	Super::Release();
}

void CatHelicopterAnimInstance::Update()
{
	Super::Update();
	CatHelicopter* cat = Cast<CatHelicopter>(owner);
	switch (cat->GetCatHelicopterKinds())
	{
	case CatHelicopterKinds::Pink:
		PlayingAnimation("Pink");
		break;
	case CatHelicopterKinds::Yellow:
		PlayingAnimation("Yellow");
		break;
	default:
		break;
	}

}

void CatHelicopterAnimInstance::Render()
{
	Super::Render();
}
