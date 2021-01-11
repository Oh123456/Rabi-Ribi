#pragma once
#include "Animinstance.h"
class BunnyBandAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	BunnyBandAnimInstance();
	~BunnyBandAnimInstance();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;


	void SetOwner(class Actor* owner) override;
private:
	void ChangeBunnyBandAnimation(IAnimation* findAnim);
	void PlayingBunnyBandAnimation(string animkeyValue);
private:
	ImageInfo* bunnyBandimageInfo;
	IAnimation* playingBunnyBandAnimation;

	map<string, IAnimation*> bunnyBandAnimations;
};

