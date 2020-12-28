#pragma once
#include "Actor.h"

DELEGATE(OnTerrainCollion);


class Character :public Actor
{
	SUPER(Actor);
public:
	Character()  : isFalling(true) , hp(0), maxHP(0) , damage(0) , moveSpeed(0){  };
	~Character() override {};


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
	void MoveCharacter();
	void MoveCancel(bool isSide = true, bool isUp = true);
	void MoveToNewGeomtryLocation(const Location& newLocation );
public:
	// �������� �浹
	OnTerrainCollion onTerrainCollion;
protected:
	int hp;
	int maxHP;
	int damage;
	float moveSpeed;
	bool isFalling;
	float acceleration;


};