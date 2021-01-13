#pragma once
#include "Enemy.h"
enum class CatHelicopterKinds
{
	Pink,
	Yellow
};

class CatHelicopter : public Enemy
{
	SUPER(Enemy);
public:
	CatHelicopter();
	~CatHelicopter();

	HRESULT Init()	override;
	void Update()	override;
	void MoveCharacter(Vector2_F speed) override;
	void NomalAttack(float ratio = 1.0f);
	void Attack();
	
	GetSetFunction(CatHelicopterKinds, CatHelicopterKinds, kinds);
protected:
	CatHelicopterKinds kinds;
};

