#pragma once
#include "Animinstance.h"
class CatHelicopterAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	CatHelicopterAnimInstance();
	~CatHelicopterAnimInstance();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
};

