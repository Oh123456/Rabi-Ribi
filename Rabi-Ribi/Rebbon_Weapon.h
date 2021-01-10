#pragma once
#include "Weapon.h"
#include "Rebbon.h"

enum class Rebbon_WeaponKinds
{
	Nomal,
};

class Rebbon_Weapon : public Weapon, public Rebbon
{
	SUPER(Weapon);

	enum class ChargeAttacekStat
	{
		Chage,
		Fire,
	};
public:
	Rebbon_Weapon();
	~Rebbon_Weapon();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	void Attack();
	void ChargeAttack();
	void ChargeAttackFire();

	void AttackEnd() { isAttack = false; isChargeAttack = false; isAttackend = false; }
private:
	// 초기 위치로 이동
	void MoveToDefaultLocation();

	void MoveToAttackLocation();

	void OnFire();

	void AttackEndTimer();

	void MoveMent() override;
private:
	bool isAttack;
	bool isChargeAttack;
	bool isAttackend;
	float moveSpeed;
	float chargeTiem;
	Rebbon_WeaponKinds kinds;
	ChargeAttacekStat chargeAttackStat;

	TimerHandle attackEndTimer;
};

