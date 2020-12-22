#pragma once
#include "pch.h"
#include "Singleton.h"
#include <bitset>


#define KEY_MAX_COUNT 256
// STL bitest
/*
	set �ϳ��ϳ��� �����Ҷ� �ߺ��� ������
	��Ʈ ����
*/

class KeyManager : public Singleton<KeyManager>
{
	SUPER(Singleton<KeyManager>)

public:
	KeyManager();
	~KeyManager();

	HRESULT Init();
	void Release();
	// key�� �ѹ� ���ȴ��� �Ǵ��ϴ��Լ�
	bool IsOnceKeyDown(int Key);
	// key�� �ѹ� ���ȴٰ� �������� �Ǵ��ϴ��Լ�
	bool IsOnceKeyUP(int key);
	// key�� ������ �ִ� �� �Ǵ��ϴ� �Լ�
	bool IsStayKeyDown(int key);

	inline void SetKeyUp(int key, bool state) { keyUp.set(key,state); }
	inline void SetKeyDown(int key, bool state) { keyDown.set(key, state); }

	inline bitset<KEY_MAX_COUNT> GetKeyUp() { return keyUp; }
	inline bitset<KEY_MAX_COUNT> GetKeyDown() { return keyDown; }

private:
	bitset<KEY_MAX_COUNT> keyUp;
	bitset<KEY_MAX_COUNT> keyDown;
};

