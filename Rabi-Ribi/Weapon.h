#pragma once
#include "Actor.h"
class Weapon : public Actor
{
	SUPER(Actor);
public:
	Weapon();
	~Weapon();

	inline void SetOwner(Actor* actor)		{ owner = actor; }
	inline void SetSocket(const Location& location) { socketLocation = location; }

	inline const Actor* GetOwner()	const 	{ return owner; }
	inline const Location GetSocket() const { return socketLocation; }
protected:
	Actor* owner;
	// 주인 객채의 부착 위치
	Location socketLocation;
};

