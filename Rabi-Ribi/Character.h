#pragma once
#include "Actor.h"

DELEGATE(OnTerrainCollion);

enum class AnimationKinds
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
		moveSideValue(0.0f), moveUpValue(0.0f), delayTime(0.0f) , noAnimChange(false),
		animKinds(AnimationKinds::Idle) , isInvincible (false), invincibleTime(2.0f)
	{ };
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
	float GetInvincibleTime()			{ return invincibleTime; };

	void SetMoveLock(bool value) { isMoveLock = value; noAnimChange = value; }
	bool GetMoveLocl() const { return isMoveLock; }

	float GetAcceleration() { return acceleration; }

	int GetDamage() { return damage; }
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
	float invincibleTime;
	float acceleration;
	float delayTime;
	AnimationKinds animKinds;
private:
	float moveSideValue;
	float moveUpValue;
	TimerHandle movementTimer;
	TimerHandle invincibleTimer;
	TimerHandle hitAnimTimer;

	float timerInterval;
};