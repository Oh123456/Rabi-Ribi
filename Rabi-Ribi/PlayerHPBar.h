#pragma once
#include "HPBar.h"
class PlayerHPBar : public HPBar
{
	SUPER(HPBar);
public:
	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
private:
	ImageInfo erina;
	Matrix3x2F sclae;
};

