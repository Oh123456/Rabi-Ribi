#pragma once
#include "Animinstance.h"

class ErinaAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	ErinaAnimInstance();
	~ErinaAnimInstance();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	void ChangeAnimation(IAnimation* findAnim);
	void PlayingAnimation(string animkeyValue);
private:
	map<string, struct IAnimation*> animations;
	




};

