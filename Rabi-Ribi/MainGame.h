#pragma once
#include "Object.h"
class MainGame : public Object
{
	SUPER(Object);
public:
	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init();
	// �޸� ����
	void Release();
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update();
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render();

	void MainLoop();

private:
	bool isFPS;

};

