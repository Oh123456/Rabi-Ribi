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
	SafemapRelease(animations);
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
		playingAnimation->Render(ownerimageInfo);
	}
}

void Animinstance::SetOwner(Actor* owner)
{
	this->owner = owner; 
	this->ownerimageInfo = Cast<ImageInfo>(owner->GetImageInfo_ptr()); 
}

const IAnimation * Animinstance::GetAnimation(string KeyValue)
{
	
	map<string, IAnimation*>::const_iterator c_it = animations.find(KeyValue);
	if (c_it == animations.end())
		return nullptr;
	return c_it->second;
}

void Animinstance::ChangeAnimation(IAnimation * findAnim)
{
	map<string, struct IAnimation*>::const_iterator c_it;
	for (c_it = animations.begin(); c_it != animations.end(); c_it++)
	{
		if (c_it->second != findAnim)
			c_it->second->Stop();
	}
}

void Animinstance::PlayingAnimation(string animkeyValue)
{
	IAnimation* anim = animations.find(animkeyValue)->second;
	ChangeAnimation(anim);
	if (!anim->IsPlaying())
	{
		anim->Play();
		playingAnimation = anim;
	}
}
