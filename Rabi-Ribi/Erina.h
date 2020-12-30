#pragma once
#include "Character.h"

//player



#define JUM_KEYDOWN_TIME 0.10f
class Erina : public Character
{
	SUPER(Character);
public:
	Erina();
	~Erina();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;


	void PlayerInputSetting(class PlayerInput* playerInput) override;

private:
	void MoveUP();
	void MoveSide();
private:
	float jumKeyDownTime;
	class Hammer* pikoHammer;
};

