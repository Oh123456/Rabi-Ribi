#pragma once
#include "pch.h"
#include "Singleton.h"
#include <bitset>


#define KEY_MAX_COUNT 256
// STL bitest
/*
	set 하나하나가 유일할때 중복이 없을때
	비트 단위
*/

class KeyManager : public Singleton<KeyManager>
{
	SUPER(Singleton<KeyManager>)

public:
	KeyManager();
	~KeyManager();

	HRESULT Init();
	void Release();
	// key가 한번 눌렸는지 판단하는함수
	bool IsOnceKeyDown(int Key);
	// key가 한번 눌렸다가 때졌는지 판단하는함수
	bool IsOnceKeyUP(int key);
	// key가 눌려져 있는 지 판단하는 함수
	bool IsStayKeyDown(int key);

	inline void SetKeyUp(int key, bool state) { keyUp.set(key,state); }
	inline void SetKeyDown(int key, bool state) { keyDown.set(key, state); }

	inline bitset<KEY_MAX_COUNT> GetKeyUp() { return keyUp; }
	inline bitset<KEY_MAX_COUNT> GetKeyDown() { return keyDown; }

private:
	bitset<KEY_MAX_COUNT> keyUp;
	bitset<KEY_MAX_COUNT> keyDown;
};

