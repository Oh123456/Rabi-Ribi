#pragma once
#include "FallingProjectile.h"

class Bomb : public FallingProjectile
{
	SUPER(FallingProjectile);

public:
	Bomb();
	~Bomb();

	HRESULT Init()	override;
	void Update()	override;
	void Release()	override;
	
	void SetDamage(int damage) { this->damage = damage; }

protected:
	void OnHit(Object* object) override;
private:
	void ExplosionTimer();
	virtual void Explosion() = 0;
protected:
	bool isHit;
	TimerHandle explosionTimer;
	int damage;
	bool isExplosion;
};

