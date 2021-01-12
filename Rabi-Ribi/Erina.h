#pragma once
#include "Character.h"

//player




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
	void MoveUP_KeyUP();
	void MoveSide();

	void AttackPikoHammer();
	void RebbonAttack();
	void RebbonChargeAttack();
	void RebbonChagetAttackFire();
	void CarrotBomb();

	void OnHit(Object* object);
private:
	class Hammer* pikoHammer;
	class Rebbon_Weapon* rebbon;
	bool isNextAttack;
};

