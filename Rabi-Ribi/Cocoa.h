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
	// ��������Ʈ ���ε�
	void SetBackJumpShot();
	void BoomAttack();

	void CallCatHelicoter();
	void CallTwoCatHelicoter();

	Vector2_F MoveFont();
	class CatHelicopter** GetCatHelicopter() { return cat; }
private:
	void JumpShot();
public:
	// BackJumpShot �Լ����� JumpShot�� �ѹ��� ȣ���ϰԲ� ��������� 
	// Delegate���� ȣ���� JumpShot���� UnBind�����ν� JumpShot�Լ��� 
	// �ѹ��� ȣ���� �ȴ�.
	OnBackJumpShot onBackJumpShot;

	class CatHelicopter* cat[2];
};

