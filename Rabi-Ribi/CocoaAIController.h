#pragma once
#include "AIBase.h"
class CocoaAIController : public AIBase
{
	SUPER(AIBase);
public:
	CocoaAIController();
	~CocoaAIController();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

private:
	void BackJumpMove();

	bool jumptest;
};

