#pragma once
#include "Character.h"

DELEGATE_OneParam(OnSee, Object*);
class Enemy : public Character
{
	SUPER(Character);
public:
	Enemy();
	~Enemy();

	void Update()	override;
	// �浿ó���� ĳ���� �����ϋ� ���
	void MoveCharacter() override;
	void Render() override;

	// ��ĳ���� �����϶� ���
	virtual void MoveCharacter(Vector2_F speed);

	GeometryCollision* GetSeeArea() const { return seeArea; }
	const SIZE_F& GetSeeAreaSize() const { return seeAreaSize; }
protected:
	void SettingSeeArea();
	void SettingSeeArea(SIZE_F& size);
	// �ǰ��� ����� ���� ó�� 
	void HitCharacterInvincible(Character* hitCharacter);
public:
	OnSee onSee;
protected:
	Location worldLocation;
	// �浹ó�� ������ �÷��̾ �����̸� ī�޶��� ��ǥ�� 
	//�������� ���� ��ġ�� �ٸ��� �Ǽ� ó�� ��ġ���������� 
	//���� �����ص� ����
	Location cameraLocation;


	// ���� �÷��̾ �����ִ� ����
	GeometryCollision* seeArea;
	SIZE_F seeAreaSize;
};

