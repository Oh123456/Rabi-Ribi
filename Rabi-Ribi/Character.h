#pragma once
#include "Actor.h"

DELEGATE(OnTerrainCollion);

enum class AnimationKinds
{
	Idle,
	Move_Right,
	Move_Left,
	Jump,
	DoubleJum,
	Falling,
	Hit,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Attack5,
	BombCharge,
	Bomb,
	Sliding,

};

#define JUM_KEYDOWN_TIME 0.30f
class Character :public Actor
{
	SUPER(Actor);
public:
	Character();
	~Character() override {};

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;

	inline void SetMaxHP(int value)														{ this->maxHP = value;}
	inline void SetHP(int value)														{ this->hp = value;}
	 // 체력 증감 최대 체력을 넘지 못한다
	inline void AddHP(int value)														{ this->hp += value; if (this->hp > this->maxHP) this->hp = this->maxHP;}	
	inline void SetMoveSpeed(float value)												{ this->moveSpeed = value;}

	inline int GetMaxHP()										const					{ return this->maxHP; }
	inline int GetHP()											const					{ return this->hp; }
	inline float GetMoveSpeed()									const					{ return this->moveSpeed; }

	inline void SetFalling(bool value) { this->isFalling = value; }
	inline bool GetFalling() { return this->isFalling; }

	void Jump();
	void MoveGeomtry(Location a);
	virtual void MoveCharacter();
	void MoveCancel(bool isSide , bool isUp);
	void MoveCancel(bool isSide);
	void MoveToNewGeomtryLocation(const Location& newLocation );
	virtual void TakeDamage(int damage);

	virtual void PlayerInputSetting(class PlayerInput* playerInput);

	void SetAnimKinds(AnimationKinds animKinds) { this->animKinds = animKinds; }
	AnimationKinds GetAnimKinds() { return animKinds; }

	void SetInvincibleTimer(float time);
	void SetInvincibleTimer();
	void SetInvincible(bool value)		{ isInvincible = value; }
	bool GetInvincible()		const	{ return isInvincible; }
	float GetInvincibleTime()	const   { return invincibleTime; };

	void SetMoveLock(bool value) { isMoveLock = value; noAnimChange = value; }
	bool GetMoveLocl() const { return isMoveLock; }

	void SetAcceleration(float value) { acceleration = value; }
	float GetAcceleration() { return acceleration; }

	void SetKeyLock(bool value) { isKeyLock = value; }
	bool GetKeyLock() const		{ return isKeyLock; }

	void SetDamage(int value) { damage = value; }
	int GetDamage() { return damage; }

	GetSetFunction(JumpPower,float, jumpPower);
	GetSetFunction(NoAnimChange, bool, noAnimChange);
protected:
	void MoveSideValue(float value) { moveSideValue = value; }
	void MoveUpValue(float value) { moveUpValue = value; }
private:
	void CharaterMove();
	void InvincibleTimerFun();
	void HitAnimationTimer();
public:
	// 지형과의 충돌
	OnTerrainCollion onTerrainCollion;
protected:
	int hp;
	int maxHP;
	int damage;
	float moveSpeed;
	float jumSpeed;
	bool isFalling;
	bool noAnimChange;
	bool isMoveLock;
	bool isInvincible;
	bool isKeyLock;
	bool isCanFly;
	float invincibleTime;
	float acceleration;
	float delayTime;
	float jumpPower;
	AnimationKinds animKinds;
	float jumKeyDownTime;
private:
	float moveSideValue;
	float moveUpValue;
	TimerHandle movementTimer;
	TimerHandle invincibleTimer;
	TimerHandle hitAnimTimer;

	float timerInterval;
};