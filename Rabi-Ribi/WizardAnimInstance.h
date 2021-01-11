#pragma once
#include "BunnyBandAnimInstance.h"

class WizardAnimInstance : public BunnyBandAnimInstance
{
	SUPER(BunnyBandAnimInstance);
public:
	WizardAnimInstance();
	~WizardAnimInstance();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	const string suffix[4] = 
	{
		"_r",
		"_g",
		"_b",
		"_y"
	};
};

