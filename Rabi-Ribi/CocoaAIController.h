#pragma once
#include "EnemyAIController.h"

enum class JumpStat
{
	Jump,
	Faillng,
	End,
};



class CocoaAIController : public EnemyAIController
{
	SUPER(EnemyAIController);

	// ���� ����
	const bool Left = true;
	const bool Right = false;
public:
	CocoaAIController();
	~CocoaAIController();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	void SetJumpDelayTime(float value = 0.15f) { jumpDelayTime = value; }

private:
	JumpStat BackJumpMove();
	void BackJumpShot();

private:

	float jumpDelayTime;
	float jumpTime;
	bool jumpCheck;
	// ���� true ���� false
	bool jumpBackDirection;
};

