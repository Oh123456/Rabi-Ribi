#pragma once
#include "PlayScene.h"
class StartMapScene : public PlayScene
{
	SUPER(PlayScene)
public:
	StartMapScene();
	~StartMapScene();
	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;
};

