#pragma once
#include "Eenemy.h"
class Rabbit : public Eenemy
{
	SUPER(Eenemy);
public:
	Rabbit();
	~Rabbit();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

};

