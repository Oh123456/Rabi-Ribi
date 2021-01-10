#pragma once
#include "Actor.h"
class Weapon : public Actor
{
	SUPER(Actor);
public:
	Weapon();
	~Weapon();

	void Update()	override;

	inline void SetOwner(Actor* actor)		{ owner = actor; }
	inline void SetSocket(const Location& location) { socketLocation = location; }

	inline const Actor* GetOwner()	const 	{ return owner; }
	inline const Location GetSocket() const { return socketLocation; }
protected:
	Actor* owner;
	// ÁÖÀÎ °´Ã¤ÀÇ ºÎÂø À§Ä¡
	Location socketLocation;
private:
	virtual void MoveMent();
	virtual void MoveEnd();
};

