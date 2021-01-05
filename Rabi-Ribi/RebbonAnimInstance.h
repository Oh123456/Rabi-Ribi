#pragma once
#include "Animinstance.h"

class RebbonAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	RebbonAnimInstance();
	~RebbonAnimInstance();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
};

