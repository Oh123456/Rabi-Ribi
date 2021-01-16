#pragma once
#include "HPBar.h"
class BossHPBar :public HPBar
{
	SUPER(HPBar);
public:
	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
private:
	Matrix3x2F sclae;
	ImageInfo pace;
};

