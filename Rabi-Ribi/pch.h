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
#include <set>
#include <vector>
#include <deque>
#include <wincodec.h>

#include <mmsystem.h>

#include "Types.h"
#include "VKKey.h"

// tiemGettiem 라이브러리
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib") 
#pragma comment(lib, "dxguid.lib") 
#pragma comment(lib, "winmm.lib")

using namespace D2D1;
using namespace std;

// 디버깅모드일 때 CMD 창 켜기
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

// 디버깅 메세지
#ifdef _DEBUG
#define DEBUG_MASSAGE(msg ,... )  printf(msg,##__VA_ARGS__) 
#else
#define DEBUG_MASSAGE(msg ,... )
#endif

extern HWND g_hWnd;
extern HINSTANCE	g_hInstance;
extern POINT g_ptMouse;
// 기본 윈도우 작업영역
extern D2D_SIZE_U g_defaultWindowSize;
extern DEVMODE g_dmSaved;
// 파일을 한번열었는지 파일을 열면 기본  경로가 바뀌여서 넣엇다
extern wchar_t DefaultDirectory[MAX_PATH];



#define WINSIZE_X 1280
#define WINSIZE_Y 800
#define WINSIZE_TILE_MAP_X		1600
#define WINSIZE_TILE_MAP_Y		900

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;
//#ifdef _DEBUG
//#else
//	int width = GetSystemMetrics(SM_CXSCREEN);
//	int height = GetSystemMetrics(SM_CYSCREEN);
//	rc.right = width;
//	rc.bottom = height;
//#endif // _DEBUG
	// 실제 윈도우 크기 받아오기
	AdjustWindowRect(&rc, WS_POPUPWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);

	GetClientRect(g_hWnd, &rc);
	g_defaultWindowSize = { (UINT)rc.right ,(UINT)rc.bottom };
}

enum class SIZE_F_RESULT
{
	// 검사 대상보다 넓이가 크다.
	Width_Size_Over,
	// 검사 대상보다 넓이가 작다.
	Width_Size_Under,
	// 검사 대상이랑 넓이가 같다.
	Width_Size_Same,
	// 검사 대상보다 폭이 크다.
	Height_Size_Over,
	// 검사 대상보다 폭이 작다.
	Height_Size_Under,
	// 검사 대상이랑 폭이 같다.
	Height_Size_Same,
};

struct SIZE_F_CompareResult
{
	SIZE_F_RESULT widthReult;
	SIZE_F_RESULT HeightReult;
};

//  Destination를 검사 대상으로 하여 Source를 비교한다
inline SIZE_F_CompareResult SIZE_FCompare(const SIZE_F& destination, const SIZE_F& source)
{
	SIZE_F_CompareResult result;
	if (destination.width < source.width)
		result.widthReult = SIZE_F_RESULT::Width_Size_Over;
	else if (destination.width > source.width)
		result.widthReult = SIZE_F_RESULT::Width_Size_Under;
	else
		result.widthReult = SIZE_F_RESULT::Width_Size_Same;

	if (destination.height < source.height)
		result.HeightReult = SIZE_F_RESULT::Height_Size_Over;
	else if (destination.height > source.height)
		result.HeightReult = SIZE_F_RESULT::Height_Size_Under;
	else
		result.HeightReult = SIZE_F_RESULT::Height_Size_Same;

	return result;
}

#include "Vector2F.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "TimerManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Color.h"
#include "Cast.h"
#include "GeometryInfo.h"
#include "SafeRelease.h"



#define GETMANAGER(x) x::GetSingleton()

#define IMAGEMANAGER	GETMANAGER(ImageManager)
#define KEYMANAGER		GETMANAGER(KeyManager)
#define TIMERMANAGER	GETMANAGER(TimerManager)
#define SOUNDMANAGER	GETMANAGER(SoundManager)
#define SCENEMANAGER	GETMANAGER(SceneManager)
#define CAMERA			GETMANAGER(Camera)

#define PI				3.14f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)

// Get Set 함수 간단히 값과 값반환을 해주는 함수의 매크로
#define GetSetFunction(funName,dataType,data) \
	void Set##funName(dataType value) {this->data = value;} \
	dataType Get##funName() const {return this->data;}

// Get Set 함수 간단히 값과 값반환을 해주는 함수의 매크로
#define GetSet(dataType,data) GetSetFunction(data,dataType,data)