#pragma once
#include "pch.h"
#include "Singleton.h"

class D2DGraphic : public Singleton<D2DGraphic>
{
public:
	~D2DGraphic();


	void Init(HWND hWnd );
	void Init_D3DSwapChain(HWND hWnd);
	void Release();
	ID2D1Bitmap* LoadImage_Png(LPCWSTR Name);
	void BeginDraw();
	void EndDraw();

	void BeginDraw_D3DSwapChain();
	void EndDraw_D3DSwapChain();
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//					AtlasEffect 아틀라스 효과																							 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateAtlasEffect();
	ID2D1Effect* CreateAtlasEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateAtlasEffect(ID2D1Effect* imageEffect);

	//You can use this effect to output a portion of an image but retain the region outside of the portion for use in subsequent operations.
	//이 효과를 사용하여 이미지의 일부를 출력 할 수 있지만 후속 작업에서 사용할 수 있도록 부분 외부 영역을 유지할 수 있습니다.
	void AtlasEffect(ID2D1Effect* effect, D2D1_VECTOR_4F size);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				AffineTransformEffect 아핀 효과																						 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateAffineTransformEffect();
	ID2D1Effect* CreateAffineTransformEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateAffineTransformEffect(ID2D1Effect* imageEffect);

	// 아핀 변화 효과
	// 회전 스케일 등등 가능
	void AffineTransformEffect(ID2D1Effect* effect, D2D1_MATRIX_3X2_F matrix);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				ScaleEffct		스케일 효과																								 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateScaleEffect();
	ID2D1Effect* CreateScaleEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateScaleEffect(ID2D1Effect* imageEffect);

	// 스케일 효과 
	void ScaleEffect(ID2D1Effect* Effect, D2D1_SIZE_F scaleSize, D2D1_POINT_2F centerPoint = D2D1_POINT_2F());


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				TintEffect		틴트 효과																									 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateTintEffect();
	ID2D1Effect* CreateTintEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateTintEffect(ID2D1Effect* imageEffect);

	// 이미지 색변경? 색곱하기
	void  TintEffect(ID2D1Effect* Effect, D2D1_VECTOR_4F color);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				Temperature and tint effect		온도와 색조 이펙트 효과														 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	ID2D1Effect* CreateTemperatureAndTintEffect();
	ID2D1Effect* CreateTemperatureAndTintEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateTemperatureAndTintEffect(ID2D1Effect* imageEffect);

	// 온도의 다른 틴트 이펙트 
	void TemperatureAndTintEffect(ID2D1Effect* Effect, float temperature, float tint = 1.0f);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				SpotDiffuseLightingEffect		스포트 디퓨저 조명 효과															 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateSpotDiffuseLightingEffect();
	ID2D1Effect* CreateSpotSpecularLightingEffect();
	ID2D1Effect* CreateSpotDiffuseLightingEffect(ID2D1Bitmap* bitmap);

	// lightPoint 빛을 쏘는 좌표 x(가로) , y (세로 ), z(높이)
	// alphaMask 최종적으로는 alphaMaskEffect으로 나오기에 alphaMask가 최종 드로우할 이펙트이다.
	// anlge 빛을 쏘는 각도 0 ~ 90 flaot 값
	// focus 빛을 집중해서 쏘는 크기 0 ~ 200 flaot 값
	// diffuse 빛의 반사 비율 0 ~ 1000 flaot 값
	// lightColor 빛의 색
	void SpotDiffuseLightingEffect(ID2D1Effect* imageEffect, ID2D1Effect* alphaMask ,D2D1_VECTOR_3F lightPoint, float angle = 90.0f , float focus = 1.0f , float diffuse = 1.0f, D2D1_VECTOR_3F lightColor = Vector3F(1.0f, 1.0f, 1.0f));
	// lightPoint 빛을 쏘는 좌표 x(가로) , y (세로 ), z(높이)
	// alphaMask 최종적으로는 alphaMaskEffect으로 나오기에 alphaMask가 최종 드로우할 이펙트이다.
	// anlge 빛을 쏘는 각도 0 ~ 90 flaot 값
	// focus 빛을 집중해서 쏘는 크기 0 ~ 200 flaot 값
	// diffuse 빛의 반사 비율 0 ~ 1000 flaot 값
	// lightColor 빛의 색
	void SpotSpecularLightingEffect(ID2D1Effect* imageEffect, ID2D1Effect* alphaMask, D2D1_VECTOR_3F lightPoint, float angle = 90.0f, float focus = 1.0f, float diffuse = 1.0f, D2D1_VECTOR_3F lightColor = Vector3F(1.0f, 1.0f, 1.0f));


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//								AlphaMask		알파 마스크																			 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateAlphaMaskEffect();



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//								ContrastEffect		대비 효과																			 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateContrastEffect();
	
	//contrastValue 는 -1.0f ~ 1.0f
	void ContrastEffect(ID2D1Effect* imageEffect, float contrastValue, BOOL bvalue = TRUE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//										FONT		폰트 효과																				 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	void FontCreate(LPCWSTR fontName);
	void __DrawText(LPCWSTR wstring , D2D1_RECT_F rect);


	ID2D1Factory* GetD2DFactory() 									{ return D2DFactory; }
	ID2D1HwndRenderTarget* GetD2DRenderTarget() 			{ return D2DRenderTarget;}
	ID2D1DeviceContext* GetDeviceContext() 						{ return Context;}
	IDWriteFactory* GetDWriteFactory()								{ return D2DWriteFactory; }
	IDWriteTextFormat* GetTextFormat()								{ return textFormat; };
	ID2D1SolidColorBrush* GetTextBrush()							{ return textBrush; };
	ID2D1SolidColorBrush* GetBrush()								{ return brush;}
private:

	/// 렌더 타겟
	//다른 객체를 생성하기 위한 객체
	ID2D1Factory* D2DFactory;
	// 그림을 그랠때 사용하는 객체
	ID2D1HwndRenderTarget* D2DRenderTarget;
	// 디바이스 컨텍트 여러가지 이펙트 처리
	ID2D1DeviceContext* Context;


	/// 폰트 관련
	// 폰트팩토리
	IDWriteFactory* D2DWriteFactory;
	// 폰트 포멧
	IDWriteTextFormat* textFormat;
	// 폰트 브러쉬
	ID2D1SolidColorBrush* textBrush;


	//브러쉬
	ID2D1SolidColorBrush* brush;

	// 생선된 모든 이펙트들의 배열
	//std::vector<ID2D1Effect*>  createdD2DEffect;
	//std::list<ID2D1Bitmap*> bitmaplist;
	//// 렌더 타겟
	//ID2D1BitmapRenderTarget* D2DbitMapRenderTarget;
};


typedef D2DGraphic D2D;
