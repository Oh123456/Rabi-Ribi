#pragma once
#include "Object.h"
class TestRoom : public Object
{
	SUPER(Object)
public:
	TestRoom();
	~TestRoom();
	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init() override;
	// �޸� ����
	void Release() override;
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update() override;
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render() override;

private:
	ImageInfo testbg;
	class Actor* player;
	class TileMap* test;
};

