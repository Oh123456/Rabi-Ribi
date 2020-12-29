#include "Animinstance.h"
#include "Animation.h"
#include "Actor.h"

Animinstance::Animinstance()
{
}

Animinstance::~Animinstance()
{
}

HRESULT Animinstance::Init()
{
	return E_NOTIMPL;
}

void Animinstance::Release()
{
}

void Animinstance::Update()
{
}

void Animinstance::Render()
{
	if (owner == nullptr)
		return;
	if (playingAnimation)
	{
		if (ownerimageInfo == nullptr)
			ownerimageInfo = Cast<ImageInfo>(owner->GetImageInfo_ptr());
		playingAnimation->Render(ownerimageInfo);
	}
}
