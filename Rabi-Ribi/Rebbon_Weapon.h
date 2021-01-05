#pragma once
#include "Weapon.h"
#include "Rebbon.h"
class Rebbon_Weapon : public Weapon, public Rebbon
{
	SUPER(Weapon);
public:
	Rebbon_Weapon();
	~Rebbon_Weapon();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	void Attack();
private:
	// 초기 위치로 이동
	void MoveToDefaultLocation();

	void MoveToAttackLocation();
private:
	bool isAttack;
	float moveSpeed;
};

