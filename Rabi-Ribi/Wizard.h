#pragma once
#include "BunnyBand.h"

enum class WizardType
{
	Red,
	Green,
	Blue,
	Yellow,
};

class Wizard : public BunnyBand
{
	SUPER(BunnyBand);
public:
	Wizard();
	~Wizard() override;

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	void MoveCharacter(Vector2_F speed) override;



	void SetWizardType(WizardType type)			{ wizardType = type; }
	WizardType GetWizardType()			const	{ return wizardType; }

protected:
	ImageInfo bunnyBand;
	WizardType wizardType;
private:
};

