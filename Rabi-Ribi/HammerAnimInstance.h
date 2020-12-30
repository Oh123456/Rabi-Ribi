#pragma once
#include "Animinstance.h"
class HammerAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	HammerAnimInstance();
	~HammerAnimInstance();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

};

