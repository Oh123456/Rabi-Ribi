#pragma once
#include "AIBase.h"
class EnemyAIController : public AIBase
{
	SUPER(AIBase);
public:
	EnemyAIController();
	~EnemyAIController();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	void SetTaget(class Actor* object) { taget = object; }
	const class Actor* GetTaget()				const { return taget; }
protected:
	class Actor* taget;
};

