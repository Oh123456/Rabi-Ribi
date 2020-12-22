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
	//					AtlasEffect ��Ʋ�� ȿ��																							 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateAtlasEffect();
	ID2D1Effect* CreateAtlasEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateAtlasEffect(ID2D1Effect* imageEffect);

	//You can use this effect to output a portion of an image but retain the region outside of the portion for use in subsequent operations.
	//�� ȿ���� ����Ͽ� �̹����� �Ϻθ� ��� �� �� ������ �ļ� �۾����� ����� �� �ֵ��� �κ� �ܺ� ������ ������ �� �ֽ��ϴ�.
	void AtlasEffect(ID2D1Effect* effect, D2D1_VECTOR_4F size);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				AffineTransformEffect ���� ȿ��																						 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateAffineTransformEffect();
	ID2D1Effect* CreateAffineTransformEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateAffineTransformEffect(ID2D1Effect* imageEffect);

	// ���� ��ȭ ȿ��
	// ȸ�� ������ ��� ����
	void AffineTransformEffect(ID2D1Effect* effect, D2D1_MATRIX_3X2_F matrix);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				ScaleEffct		������ ȿ��																								 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateScaleEffect();
	ID2D1Effect* CreateScaleEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateScaleEffect(ID2D1Effect* imageEffect);

	// ������ ȿ�� 
	void ScaleEffect(ID2D1Effect* Effect, D2D1_SIZE_F scaleSize, D2D1_POINT_2F centerPoint = D2D1_POINT_2F());


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				TintEffect		ƾƮ ȿ��																									 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateTintEffect();
	ID2D1Effect* CreateTintEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateTintEffect(ID2D1Effect* imageEffect);

	// �̹��� ������? �����ϱ�
	void  TintEffect(ID2D1Effect* Effect, D2D1_VECTOR_4F color);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				Temperature and tint effect		�µ��� ���� ����Ʈ ȿ��														 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	ID2D1Effect* CreateTemperatureAndTintEffect();
	ID2D1Effect* CreateTemperatureAndTintEffect(ID2D1Bitmap* bitmap);
	ID2D1Effect* CreateTemperatureAndTintEffect(ID2D1Effect* imageEffect);

	// �µ��� �ٸ� ƾƮ ����Ʈ 
	void TemperatureAndTintEffect(ID2D1Effect* Effect, float temperature, float tint = 1.0f);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//				SpotDiffuseLightingEffect		����Ʈ ��ǻ�� ���� ȿ��															 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateSpotDiffuseLightingEffect();
	ID2D1Effect* CreateSpotSpecularLightingEffect();
	ID2D1Effect* CreateSpotDiffuseLightingEffect(ID2D1Bitmap* bitmap);

	// lightPoint ���� ��� ��ǥ x(����) , y (���� ), z(����)
	// alphaMask ���������δ� alphaMaskEffect���� �����⿡ alphaMask�� ���� ��ο��� ����Ʈ�̴�.
	// anlge ���� ��� ���� 0 ~ 90 flaot ��
	// focus ���� �����ؼ� ��� ũ�� 0 ~ 200 flaot ��
	// diffuse ���� �ݻ� ���� 0 ~ 1000 flaot ��
	// lightColor ���� ��
	void SpotDiffuseLightingEffect(ID2D1Effect* imageEffect, ID2D1Effect* alphaMask ,D2D1_VECTOR_3F lightPoint, float angle = 90.0f , float focus = 1.0f , float diffuse = 1.0f, D2D1_VECTOR_3F lightColor = Vector3F(1.0f, 1.0f, 1.0f));
	// lightPoint ���� ��� ��ǥ x(����) , y (���� ), z(����)
	// alphaMask ���������δ� alphaMaskEffect���� �����⿡ alphaMask�� ���� ��ο��� ����Ʈ�̴�.
	// anlge ���� ��� ���� 0 ~ 90 flaot ��
	// focus ���� �����ؼ� ��� ũ�� 0 ~ 200 flaot ��
	// diffuse ���� �ݻ� ���� 0 ~ 1000 flaot ��
	// lightColor ���� ��
	void SpotSpecularLightingEffect(ID2D1Effect* imageEffect, ID2D1Effect* alphaMask, D2D1_VECTOR_3F lightPoint, float angle = 90.0f, float focus = 1.0f, float diffuse = 1.0f, D2D1_VECTOR_3F lightColor = Vector3F(1.0f, 1.0f, 1.0f));


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//								AlphaMask		���� ����ũ																			 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateAlphaMaskEffect();



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//								ContrastEffect		��� ȿ��																			 //
	//																																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ID2D1Effect* CreateContrastEffect();
	
	//contrastValue �� -1.0f ~ 1.0f
	void ContrastEffect(ID2D1Effect* imageEffect, float contrastValue, BOOL bvalue = TRUE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//																																			 //
	//										FONT		��Ʈ ȿ��																				 //
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

	/// ���� Ÿ��
	//�ٸ� ��ü�� �����ϱ� ���� ��ü
	ID2D1Factory* D2DFactory;
	// �׸��� �׷��� ����ϴ� ��ü
	ID2D1HwndRenderTarget* D2DRenderTarget;
	// ����̽� ����Ʈ �������� ����Ʈ ó��
	ID2D1DeviceContext* Context;


	/// ��Ʈ ����
	// ��Ʈ���丮
	IDWriteFactory* D2DWriteFactory;
	// ��Ʈ ����
	IDWriteTextFormat* textFormat;
	// ��Ʈ �귯��
	ID2D1SolidColorBrush* textBrush;


	//�귯��
	ID2D1SolidColorBrush* brush;

	// ������ ��� ����Ʈ���� �迭
	//std::vector<ID2D1Effect*>  createdD2DEffect;
	//std::list<ID2D1Bitmap*> bitmaplist;
	//// ���� Ÿ��
	//ID2D1BitmapRenderTarget* D2DbitMapRenderTarget;
};


typedef D2DGraphic D2D;
