#pragma once
#include "Animinstance.h"
class ProjectileAnimInstance : public Animinstance
{
	SUPER(Animinstance);
public:
	ProjectileAnimInstance();
	~ProjectileAnimInstance();


	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
};

