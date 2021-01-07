#pragma once
#include "Enemy.h"
class Rabbit : public Enemy
{
	SUPER(Enemy);
public:
	Rabbit();
	~Rabbit();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	void MoveCharacter(Vector2_F speed) override;

private:
	void OnSee(Object* object);
	void OnHit(Object* object);
	void Jum();

private:
	TimerHandle jumTimer;
	int jumTimerCount;
};

