#pragma once
#include "Object.h"

class Animinstance : public Object
{
public:
	Animinstance();
	~Animinstance();
	
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
	
	void SetOwner(class Actor* owner) { this->owner = owner; }
protected:
	struct IAnimation* playingAnimation;
	class Actor* owner;
	ImageInfo* ownerimageInfo;
};

