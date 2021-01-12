#pragma once
#include "EnemyAIController.h"
class CocoaAIController : public EnemyAIController
{
	SUPER(EnemyAIController);

	// 점프 방향
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
	void BackJumpMove();
	float jumpDelayTime;
	float jumpTime;
	bool jumpCheck;
	// 좌측 true 우측 false
	bool jumpBackDirection;
};

