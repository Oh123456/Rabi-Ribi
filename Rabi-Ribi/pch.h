#pragma once
#include <Windows.h>
#include <iostream>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d2d1effects_2.h>
#include <dwrite.h>
#include <dsound.h>
#include <mmsystem.h>
#include <wchar.h>
#include <list>
#include <map>
#include <vector>
#include <wincodec.h>

#include <mmsystem.h>

#include "Types.h"
#include "VKKey.h"

// tiemGettiem ���̺귯��
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib") 
#pragma comment(lib, "dxguid.lib") 
#pragma comment(lib, "winmm.lib")

using namespace D2D1;
using namespace std;

// ��������� �� CMD â �ѱ�
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

// ����� �޼���
#ifdef _DEBUG
#define DEBUG_MASSAGE(msg ,... )  printf(msg,##__VA_ARGS__) 
#else
#define DEBUG_MASSAGE(msg ,... )
#endif


//#define EFFECT_CHECK(x) if( x == nullptr)
extern HWND g_hWnd;
extern HINSTANCE	g_hInstance;
extern POINT g_ptMouse;

struct Location
{
	float x = 0.0f;
	float y = 0.0f;
};

// ���̳��� ĳ��Ʈ
template<typename T, typename U>
T* Cast(U* src)
{
	return dynamic_cast<T*>(src);
}

// ��Ÿƽ ĳ��Ʈ
template<typename T, typename U>
T Cast(U src)
{
	return static_cast<T>(src);
}

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{

#ifdef _DEBUG
	// ������ �۾����� ����
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;
#else
	// ��ü ȭ��
	DEVMODE dmSaved;
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSaved);

	// ������ �۾����� ����
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = dmSaved.dmPelsWidth;
	rc.bottom = dmSaved.dmPelsHeight;
#endif // _DEBUG



	// ���� ������ ũ�� �޾ƿ���
	AdjustWindowRect(&rc, WS_POPUPWINDOW, false);

	// �̵�
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}


#include "ImageManager.h"
#include "KeyManager.h"
#include "TimerManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Color.h"


#define GETMANAGER(x) x::GetSingleton()

#define IMAGEMANAGER	GETMANAGER(ImageManager)
#define KEYMANAGER		GETMANAGER(KeyManager)
#define TIMERMANAGER	GETMANAGER(TimerManager)
#define SOUNDMANAGER	GETMANAGER(SoundManager)
#define SCENEMANAGER	GETMANAGER(SceneManager)


#define WINSIZE_X 1280
#define WINSIZE_Y 800
#define WINSIZE_TILE_MAP_X		1600
#define WINSIZE_TILE_MAP_Y		900

#define SAFE_DELETE(x) \
if (x) \
{\
	delete x;\
	x = nullptr; \
}

#define SAFE_ARR_DELETE(x) \
if (x) \
{\
	delete[] x;\
	x = nullptr; \
}


#define SAFE_RELEASE(x) \
 if (x)\
{ \
 	x->Release(); \
	x = nullptr; \
}