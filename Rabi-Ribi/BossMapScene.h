#pragma once
#include "PlayScene.h"
class BossMapScene : public PlayScene
{
	SUPER(PlayScene)
public:
	BossMapScene();
	~BossMapScene();
	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;
};

