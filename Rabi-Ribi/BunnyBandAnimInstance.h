#pragma once
#include "Animinstance.h"
class BunnyBandAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	BunnyBandAnimInstance();
	~BunnyBandAnimInstance();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
};

