#pragma once
#include "EnemyAIController.h"
class CatAIController : public EnemyAIController
{
	SUPER(EnemyAIController);
public:
	CatAIController();
	~CatAIController();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	void AttackDelay();
	void TunMove_8AttackDelay();
	void TagetAttackDelay();
	void PattenMove();
	void Exit();
private:
	TimerHandle timer;
	int attackCount;
	int exitCount;
	bool isTagetMove;
	bool isAttack;
	bool isExit;
	float delay;
	float nomalAttackspeed;

};

