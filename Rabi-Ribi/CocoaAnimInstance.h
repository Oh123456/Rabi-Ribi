#pragma once
#include "Animinstance.h"
class CocoaAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	CocoaAnimInstance();
	~CocoaAnimInstance();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	void AnimationEnd();
private:
	TimerHandle timer;
};

