#pragma once
#include "Bomb.h"
class BlackBomb : public Bomb
{
	SUPER(Bomb);
public:
	BlackBomb();
	~BlackBomb();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	void Explosion() override;

	void ExplosionHit(Object* object);
};

