#pragma once
#include "Object.h"
class HUD : public Object
{
	SUPER(Object);
public:
	HUD();
	~HUD();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	class HPBar* playerHPBar;
	class HPBar* bossHPBar;
};

