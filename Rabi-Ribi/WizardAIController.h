#pragma once
#include "EnemyAIController.h"
class WizardAIController : public EnemyAIController
{
	SUPER(EnemyAIController);
public:
	WizardAIController();
	~WizardAIController();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
};

