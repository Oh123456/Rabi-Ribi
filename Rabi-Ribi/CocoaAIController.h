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

	// 점프 방향
	const bool Left = true;
	const bool Right = false;

	enum class JumpKinds
	{
		BackJump,
		BackShotJum,
	};
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

	void Patten();
private:

	float jumpDelayTime;
	float jumpTime;
	bool jumpCheck;
	JumpKinds jumpKinds;
	// 좌측 true 우측 false
	bool jumpBackDirection;
	Actor* catHelicopter;
	TimerHandle pattenTimer;
};

