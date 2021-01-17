#pragma once
#include "Actor.h"
class MoveActor :public Actor
{
	SUPER(Actor);
public:
	MoveActor();
	~MoveActor();

	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;

	GetSetFunction(MoveStage, class Stage*, moveStage);

private:
	void OnHit(Object* obejct);
	class Stage* moveStage;
};

