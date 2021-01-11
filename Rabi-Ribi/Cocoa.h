#pragma once
#include "Enemy.h"
class Cocoa : public Enemy
{
	SUPER(Enemy);
public:
	Cocoa();
	~Cocoa();

	HRESULT Init()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;

	void MoveCharacter(Vector2_F speed) override;
};

