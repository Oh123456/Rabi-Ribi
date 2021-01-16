#pragma once
#include "Enemy.h"



DELEGATE(OnBackJumpShot);

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
	void TakeDamage(int damage) override;
	// 델리게이트 반인드
	void SetBackJumpShot();
	void BoomAttack();

	void CallCatHelicoter();
	void CallTwoCatHelicoter();

	Vector2_F MoveFont();
	class CatHelicopter** GetCatHelicopter() { return cat; }
private:
	void JumpShot();
public:
	// BackJumpShot 함수에서 JumpShot을 한번만 호출하게끔 만들기위해 
	// Delegate선언 호출후 JumpShot에서 UnBind함으로써 JumpShot함수가 
	// 한번만 호출이 된다.
	OnBackJumpShot onBackJumpShot;

	class CatHelicopter* cat[2];
};

