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
		함수 호출 시점에 가상키가 어떤 상태인지 확인이 가능하다
		1. 0x0000 => 이전 프레임에 누른적이 없고 호출 시점에도 눌려있지 않음
		2. 0x0001 => 이전 프레임에 눌른적이 있고 호출 시점에는 눌려있지 않음
		3. 0x8000 => 이전 프레임에 눌른적이 없고 호출 시점에는 눌려있는 상태
		4. 0x8001 => 이전 프레임에 눌른적이 있고 호출 시점에도 눌려있는 상태
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
		함수 호출 시점에 가상키가 어떤 상태인지 확인이 가능하다
		1. 0x0000 => 이전 프레임에 누른적이 없고 호출 시점에도 눌려있지 않음
		2. 0x0001 => 이전 프레임에 눌른적이 있고 호출 시점에는 눌려있지 않음
		3. 0x8000 => 이전 프레임에 눌른적이 없고 호출 시점에는 눌려있는 상태
		4. 0x8001 => 이전 프레임에 눌른적이 있고 호출 시점에도 눌려있는 상태
	*/
	//DEBUG_MASSAGE("%x" ,GetAsyncKeyState(key));
	if (GetAsyncKeyState(key) & 0x8000)
	{
		// 키다운상태 키업 체크임으로 키업을 false로
		if (keyUp[key])
			keyUp[key] = false;
		return false;
	}
	else
	{
		// 키업 상태 키업이랑 키다운 변경
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
