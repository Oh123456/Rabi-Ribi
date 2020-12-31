#pragma once
#include "Animinstance.h"
class RabbitAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	RabbitAnimInstance();
	~RabbitAnimInstance();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

};

