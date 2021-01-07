#pragma once
#include "Animinstance.h"

class ErinaAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	ErinaAnimInstance();
	~ErinaAnimInstance();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
};

