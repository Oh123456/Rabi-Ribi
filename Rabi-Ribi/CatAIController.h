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
};

