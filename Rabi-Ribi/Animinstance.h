#pragma once
#include "Object.h"

struct IAnimation;
class Animinstance : public Object
{
	SUPER(Object);
public:
	Animinstance();
	~Animinstance();
	
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
	
	virtual void SetOwner(class Actor* owner);
	const IAnimation* GetPlayingAnimation() const { return playingAnimation; }
	const IAnimation* GetAnimation(string KeyValue);

protected:
	void ChangeAnimation(IAnimation* findAnim);
	void PlayingAnimation(string animkeyValue);
protected:
	IAnimation* playingAnimation;
	class Actor* owner;
	ImageInfo* ownerimageInfo;
	map<string, IAnimation*> animations;
};

