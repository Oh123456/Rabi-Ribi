#pragma once
#include "Bomb.h"
class CarrotBomb : public Bomb
{
	SUPER(Bomb);

public:
	CarrotBomb();
	~CarrotBomb();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	void Explosion() override;

	void ExplosionHit(Object* object);
private:


};

