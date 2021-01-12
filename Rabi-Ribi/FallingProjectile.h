#pragma once
#include "Projectile.h"
class FallingProjectile : public Projectile
{
	SUPER(Projectile);

public:
	FallingProjectile();
	~FallingProjectile();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	void SetSpeed(Vector2_F speed) override;
	void SetSpeed(float xValue);
	void SetIsValid(bool value) override;

	void SetAcceleration(float value) { acceleration = value; }
	float GetAcceleration() const { return acceleration; }


protected:
	virtual void OnHit(Object* object);
private:
	void MoveMent()override;
	void MoveEnd(Location& wolrdLocation) override;

	void Acceleration();
protected:
	float acceleration;
	float moveMentX;
	float boundvalue;
	TimerHandle accelerationTimer;
};

