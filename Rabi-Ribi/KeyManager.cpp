#include "KeyManager.h"

KeyManager::KeyManager()
{
	this->Init();
}

KeyManager::~KeyManager()
{
}

HRESULT KeyManager::Init()
{
	for (int i = 0; i < KEY_MAX_COUNT; i++)
	{
		keyUp[i] = true;
		keyDown[i] = false;
	}

	return S_OK;
}

void KeyManager::Release()
{
	Super::ReleaseSingleton();
}

bool KeyManager::IsOnceKeyDown(int key)
{
	// GetAsyncKeyState
	/*
		�Լ� ȣ�� ������ ����Ű�� � �������� Ȯ���� �����ϴ�
		1. 0x0000 => ���� �����ӿ� �������� ���� ȣ�� �������� �������� ����
		2. 0x0001 => ���� �����ӿ� �������� �ְ� ȣ�� �������� �������� ����
		3. 0x8000 => ���� �����ӿ� �������� ���� ȣ�� �������� �����ִ� ����
		4. 0x8001 => ���� �����ӿ� �������� �ְ� ȣ�� �������� �����ִ� ����
	*/
	//DEBUG_MASSAGE("%x", GetAsyncKeyState(key));
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (keyDown[key] == false)
		{
			keyDown[key] = true;
			return true;
		}
	}
	else
		keyDown[key] = false;
	return false;
}

bool KeyManager::IsOnceKeyUP(int key)
{

	// GetAsyncKeyState
	/*
		�Լ� ȣ�� ������ ����Ű�� � �������� Ȯ���� �����ϴ�
		1. 0x0000 => ���� �����ӿ� �������� ���� ȣ�� �������� �������� ����
		2. 0x0001 => ���� �����ӿ� �������� �ְ� ȣ�� �������� �������� ����
		3. 0x8000 => ���� �����ӿ� �������� ���� ȣ�� �������� �����ִ� ����
		4. 0x8001 => ���� �����ӿ� �������� �ְ� ȣ�� �������� �����ִ� ����
	*/
	//DEBUG_MASSAGE("%x" ,GetAsyncKeyState(key));
	if (GetAsyncKeyState(key) & 0x8000)
	{
		// Ű�ٿ���� Ű�� üũ������ Ű���� false��
		if (keyUp[key])
			keyUp[key] = false;
		return false;
	}
	else
	{
		// Ű�� ���� Ű���̶� Ű�ٿ� ����
		if  (keyUp[key] == false)
		{
			keyUp[key] = true;
			return true;
		}
	}
	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		keyDown[key] = true;
		return true;
	}
	else
		keyDown[key] = false;
	return false;
}
