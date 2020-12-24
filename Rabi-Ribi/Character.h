#pragma once
#include "Actor.h"

DELEGATE(OnTerrainCollion);


class Character :public Actor
{
	SUPER(Actor);
public:
	Character() {  };
	~Character() override {};


	inline void SetMaxHP(int value)														{ this->maxHP = value;}
	inline void SetHP(int value)														{ this->hp = value;}
	 // 체력 증감 최대 체력을 넘지 못한다
	inline void AddHP(int value)														{ this->hp += value; if (this->hp > this->maxHP) this->hp = this->maxHP;}	
	inline void SetMoveSpeed(float value)												{ this->moveSpeed = value;}

	inline int GetMaxHP()										const					{ return this->maxHP; }
	inline int GetHP()											const					{ return this->hp; }
	inline float GetMoveSpeed()									const					{ return this->moveSpeed; }

public:
	// 지형과의 충돌
	OnTerrainCollion onTerrainCollion;

protected:
	int hp;
	int maxHP;
	int damage;
	float moveSpeed;



};