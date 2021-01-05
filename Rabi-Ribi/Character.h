#pragma once
#include "Actor.h"

DELEGATE(OnTerrainCollion);

enum class AnimmationKinds
{
	Idle,
	Move_Right,
	Move_Left,
	Jum,
	Falling,
	Hit,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
};

class Character :public Actor
{
	SUPER(Actor);
public:
	Character()  :
		isFalling(true) , hp(0), maxHP(0) , damage(0) , moveSpeed(0.0f) , jumSpeed(0.0f) ,
		moveSideValue(0.0f), moveUpValue(0.0f), delayTime(0.0f) , moveLock(false),animKinds(AnimmationKinds::Idle){ };
	~Character() override {};

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;

	inline void SetMaxHP(int value)														{ this->maxHP = value;}
	inline void SetHP(int value)														{ this->hp = value;}
	 // ü�� ���� �ִ� ü���� ���� ���Ѵ�
	inline void AddHP(int value)														{ this->hp += value; if (this->hp > this->maxHP) this->hp = this->maxHP;}	
	inline void SetMoveSpeed(float value)												{ this->moveSpeed = value;}

	inline int GetMaxHP()										const					{ return this->maxHP; }
	inline int GetHP()											const					{ return this->hp; }
	inline float GetMoveSpeed()									const					{ return this->moveSpeed; }

	inline void SetFalling(bool value) { this->isFalling = value; }
	inline bool GetFalling() { return this->isFalling; }

	void MoveGeomtry(Location a);
	virtual void MoveCharacter();
	void MoveCancel(bool isSide = true, bool isUp = true);
	void MoveToNewGeomtryLocation(const Location& newLocation );

	virtual void PlayerInputSetting(class PlayerInput* playerInput);

	void SetAnimKinds(AnimmationKinds animKinds) { this->animKinds = animKinds; }
	AnimmationKinds GetAnimKinds() { return animKinds; }

	void SetMoveLock(bool value) { moveLock = value; }
	bool GetMoveLocl() const { return moveLock; }

	float GetAcceleration() { return acceleration; }
protected:
	void MoveSideValue(float value) { moveSideValue = value; }
	void MoveUpValue(float value) { moveUpValue = value; }
private:
	void CharaterMove();
public:
	// �������� �浹
	OnTerrainCollion onTerrainCollion;
protected:
	int hp;
	int maxHP;
	int damage;
	float moveSpeed;
	float jumSpeed;
	bool isFalling;
	bool moveLock;
	float acceleration;
	float delayTime;
	AnimmationKinds animKinds;
private:
	float moveSideValue;
	float moveUpValue;
private:
	TimerHandle movementTimer;
	float timerInterval;
};