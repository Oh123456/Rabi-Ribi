#pragma once
#include "Character.h"

//player



#define JUM_KEYDOWN_TIME 0.20f
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

	void SetNextAttack(bool value) { isNextAttack = value; }
	bool GetNextAttack() const { return isNextAttack; }

	class Hammer* GetPikoHammer() { return pikoHammer; }
private:
	void MoveUP();
	void MoveSide();

	void AttackPikoHammer();
private:
	float jumKeyDownTime;
	class Hammer* pikoHammer;
	bool isNextAttack;
};

