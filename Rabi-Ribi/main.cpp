#include "D2DGraphic.h"
#include "pch.h"
#include "MainGame.h"

using namespace D2D1;

// 전역번수
HINSTANCE	g_hInstance;			// 프로그램 인스턴스 핸들  (메모리상의 객체 == 인스턴스)
HWND		g_hWnd;				// 윈도우 핸들 
LPSTR		g_lpszClass = (LPSTR)(TEXT("과거의 나여 잘했다"));//const_cast<LPSTR>			// 윈도의 이름
POINT		g_ptMouse;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
D2D_SIZE_U	g_defaultWindowSize;
DEVMODE g_dmSaved;  // 현재 해상도를 저장.. 왜냐 게임 끝나면 원래대로 돌려야 하니깐

MainGame mainGame;

void Loop();
//메임함수
//(APIENTRY == WINAPI)
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	// 윈도우를 생성하기 위한 기본셋팅 
	g_hInstance = _hInstance;
	MSG message;
	WNDCLASS wndClass;



	wndClass.cbClsExtra = 0;				// 클래스의 여분 메모리
	wndClass.cbWndExtra = 0;				// 윈도우의 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// 윈도우 배경
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);     // (인스턴스 , 모양기본)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// (인스턴스 , 아이콘 모양)	
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc; //  (WNDPROC)WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);
	// 윈도우 생성
#ifdef _DEBUG
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, //WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT, WINSIZE_X, WINSIZE_Y,
		NULL, (HMENU)NULL, g_hInstance, NULL);
#else
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_POPUPWINDOW, //WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT, WINSIZE_X, WINSIZE_Y,
		NULL, (HMENU)NULL, g_hInstance, NULL);
#endif // _DEBUG



	SetWindowSize(0, 0, WINSIZE_X, WINSIZE_Y);
	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	D2D* d2d = D2D::GetSingleton();
	d2d->Init(g_hWnd);
	d2d->FontCreate(L"궁서체");
	
	mainGame.Init();
	//ImageManager::GetSingleton()->LoadPng(L"player_a");
	// 메시지 큐에 있는 메시지 처리 CallBack

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&message, NULL, 0, 0))
				return (int)message.wParam;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			mainGame.MainLoop();
		}

		// else 메인루프 
	}

	return (int)message.wParam;

}




// 콜백함수 : 윈도우 메시지(이벤트)를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_CREATE:
	{
		// 현재 설정을 저장
		//EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &g_dmSaved);

		//DEVMODE dmSelected;// 원하는 해상도를 저장하는 변수
		//int width = GetSystemMetrics(SM_CXSCREEN);
		//int height = GetSystemMetrics(SM_CYSCREEN);

		//memset(&dmSelected, 0, sizeof(dmSelected));
		//dmSelected.dmSize = sizeof(dmSelected);
		//dmSelected.dmPelsWidth = width;// 800
		//dmSelected.dmPelsHeight = height;// 600
		//dmSelected.dmBitsPerPel = 32;
		//dmSelected.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		//if (ChangeDisplaySettings(&dmSelected, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		//{
		//	MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
		//}
		break;
	}
	case WM_DESTROY:
		ChangeDisplaySettings(&g_dmSaved, CDS_RESET);
		mainGame.Release();
		D2D::GetSingleton()->Release();
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		break;

	}
	case WM_SIZE:
		break;
		if (D2D::GetSingleton()->GetD2DRenderTarget())
		{
			RECT rc;
			GetClientRect(g_hWnd, &rc);
			D2D::GetSingleton()->GetD2DRenderTarget()->Resize({ (UINT)rc.right,(UINT)rc.bottom });
			D2D::GetSingleton()->GetD2DRenderTarget();
		}
		break;
	case WM_KEYDOWN:
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

int j = 0;
float a = 0.0f;
int R = 0;
int countss = 8;

void Loop()
{
	D2D* d2d = D2D::GetSingleton();
	ID2D1DeviceContext* Context = d2d->GetDeviceContext();
	d2d->BeginDraw();

	ImageInfo imageInfo;

	imageInfo.imageName = L"player_a";
	imageInfo.imageLocation = { 500,300 };
	imageInfo.atlasInfo.frameSize = { 64,64 }; //= { (64.0f * j),0.0f + (0 * 64.0f), 64.0f + (64.0f * j),64.0f + (0 * 64.0f) };
	imageInfo.atlasInfo.frame = { j, 0 };
	//imageInfo.atlasSize = { (64.0f * j),0.0f + (0 * 64.0f), 64.0f + (64.0f * j),64.0f + (0 * 64.0f) };
	imageInfo.affineMatrix = Matrix3x2F::Rotation(3.5, { 32.0f ,32.0f });
	imageInfo.tintColor = D2D1::Vector4F(1.0f, 1.f, 1.0f, 1.0f);
	imageInfo.spotDiffuseInfo.lightPoint = D2D1::Vector3F(64.0f, 0.0f, 0.5f);
	imageInfo.contrasteInfo.contrast = -1.0f;
	imageInfo.temperatureInfo.temperature = 2.0f;
	imageInfo.temperatureInfo.tint = 1.0f;
	imageInfo.scaleInfo.scaleSize = { 1.0f ,1.0f };
	imageInfo.imageEffect = D2DIE_ATLAS | D2DIE_CONTRASTEFFECT | D2DIE_AFFINE;
	ImageManager::GetSingleton()->ImageRander(imageInfo);

	GETMANAGER(ImageManager);

	a += 1.0f;
	if (a >= 360.0f)
		a = 0.f;
	static int zz = 0;
	zz++;
	if (zz == 8)
	{
		j++;
		if (j == countss)
			j = 0;
		zz = 0;
	}



	d2d->EndDraw();
}
