#pragma once
#include "Character.h"
class Eenemy : public Character
{
	SUPER(Character);
public:
	Eenemy();
	~Eenemy();

	void Update()	override;
	void MoveCharacter() override;

protected:
	Location worldLocation;
	// �浹ó�� ������ �÷��̾ �����̸� ī�޶��� ��ǥ�� 
	//�������� ���� ��ġ�� �ٸ��� �Ǽ� ó�� ��ġ���������� 
	//���� �����ص� ����
	Location cameraLocation;
};

