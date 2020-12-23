#include "D2DGraphic.h"

#include <d2d1helper.h>
#include <combaseapi.h>


#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Dwrite.lib")


D2DGraphic::~D2DGraphic()
{
	//this->ClearEffct();
	//this->ClearBitmap();
	this->Release();
}

void D2DGraphic::Init(HWND hWnd)
{
	// COM ���̺귯�� ����ϱ� ���� �Լ�
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	// Direct2D�� ���� Factory ��ü ����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);


	RECT rect;
	// Ŭ���̾�Ʈ ������ ��ǥ ���
	GetClientRect(hWnd, &rect);
	D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED);
	// ������ �������� Ŭ���̾�Ʈ ������ �׸��� �׸��� ���� RenderTarget�� ��´�.
	D2DFactory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(hWnd, SizeU(rect.right, rect.bottom),D2D1_PRESENT_OPTIONS_IMMEDIATELY), &D2DRenderTarget);
	D2DRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE::D2D1_ANTIALIAS_MODE_ALIASED);
	//D2DRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(10.0f, 10.0f), &D2DbitMapRenderTarget);
	D2DRenderTarget->QueryInterface(__uuidof(ID2D1DeviceContext), (void**)&Context);

	D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);


	
}


void D2DGraphic::Release()
{
	// COM ���̺귯�� ����
	CoUninitialize();
	Context->Release();
	textBrush->Release();
	brush->Release();
	textFormat->Release();
	D2DWriteFactory->Release();
	D2DRenderTarget->Release();
	D2DFactory->Release();

}

ID2D1Bitmap* D2DGraphic::LoadImage_Png(LPCWSTR Name)
{
	// �̹��� �ε�
	// Png������ ����Ǿ� �ֱ⿡ ��Ʈ���������� ������ �����ϴ� ���ڴ�;
	ID2D1Bitmap* Result = nullptr;
	IWICImagingFactory* WICImagingFactory;
	// WIC ��ü�� �����ϱ� ���� Factory ��ü�� ����
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&WICImagingFactory));
	IWICBitmapDecoder* bitmapDecoder;
	WICImagingFactory->CreateDecoderFromFilename(Name, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &bitmapDecoder);
	// Ư�� �׸��� ������ ��ü
	IWICBitmapFrameDecode* bitmapFrameDecoder = nullptr;
	// ���� �̹��� �߿��� ù��° �̹��� ����
	bitmapDecoder->GetFrame(0, &bitmapFrameDecoder);


	// �̹��� ��ȯ
	IWICFormatConverter* Converter;
	WICImagingFactory->CreateFormatConverter(&Converter);
	// ���õ� �׸��� �� ������ ��Ʈ������ ��ȯ �Ұ����� 
	Converter->Initialize(bitmapFrameDecoder, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	// IWICBitmap������ ID2D1Bitmap���� ��ȯ
	D2DRenderTarget->CreateBitmapFromWicBitmap(Converter, NULL, &Result);
	Converter->Release();
	bitmapFrameDecoder->Release();
	bitmapDecoder->Release();
	WICImagingFactory->Release();

	//bitmaplist.push_back(Result);
	return Result;
	////////
}

void D2DGraphic::BeginDraw()
{
	if (D2DRenderTarget != nullptr)
	{
		D2DRenderTarget->BeginDraw();
		D2DRenderTarget->Clear(ColorF(0.0f, 0.0f,0.0f));
	}
}

void D2DGraphic::EndDraw()
{
	if (D2DRenderTarget != nullptr)
	{
		D2DRenderTarget->EndDraw();
		//this->ClearEffct();
	}
}


ID2D1Effect * D2DGraphic::CreateAtlasEffect()
{
	ID2D1Effect* atlasEffect;
	Context->CreateEffect(CLSID_D2D1Atlas, &atlasEffect);
	return atlasEffect;
}

ID2D1Effect* D2DGraphic::CreateAtlasEffect(ID2D1Bitmap * bitmap)
{
	ID2D1Effect* atlasEffect;
	Context->CreateEffect(CLSID_D2D1Atlas, &atlasEffect);
	atlasEffect->SetInput(0, bitmap);
	return atlasEffect;
}

ID2D1Effect* D2DGraphic::CreateAtlasEffect(ID2D1Effect * imageEffect)
{
	ID2D1Effect* atlasEffect;
	Context->CreateEffect(CLSID_D2D1Atlas, &atlasEffect);
	atlasEffect->SetInputEffect(0, imageEffect);

	return atlasEffect;
}

void D2DGraphic::AtlasEffect(ID2D1Effect * Effect, D2D1_VECTOR_4F size)
{
	Effect->SetValue(D2D1_ATLAS_PROP_INPUT_RECT, size);
	Effect->SetValue(D2D1_ATLAS_PROP_INPUT_PADDING_RECT, size);

}

ID2D1Effect * D2DGraphic::CreateAffineTransformEffect()
{
	ID2D1Effect* affineTransformEffect;
	Context->CreateEffect(CLSID_D2D12DAffineTransform, &affineTransformEffect);
	return affineTransformEffect;
}

ID2D1Effect* D2DGraphic::CreateAffineTransformEffect(ID2D1Bitmap * bitmap)
{
	ID2D1Effect* affineTransformEffect;
	Context->CreateEffect(CLSID_D2D12DAffineTransform, &affineTransformEffect);
	affineTransformEffect->SetInput(0, bitmap);
	return affineTransformEffect;
}

ID2D1Effect* D2DGraphic::CreateAffineTransformEffect(ID2D1Effect* imageEffect)
{
	ID2D1Effect* affineTransformEffect;
	Context->CreateEffect(CLSID_D2D12DAffineTransform, &affineTransformEffect);
	affineTransformEffect->SetInputEffect(0, imageEffect);
	return affineTransformEffect;
}

void D2DGraphic::AffineTransformEffect(ID2D1Effect* Effect, D2D1_MATRIX_3X2_F matrix)
{
	//Effect->SetValue(D2D1_2DAFFINETRANSFORM_PROP_INTERPOLATION_MODE, D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR);
	//Effect->SetValue(D2D1_2DAFFINETRANSFORM_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
	//Effect->SetValue(D2D1_2DAFFINETRANSFORM_PROP_SHARPNESS, 1.0f);
	Effect->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, matrix);
}

ID2D1Effect * D2DGraphic::CreateScaleEffect()
{
	ID2D1Effect* scaleEffect;
	Context->CreateEffect(CLSID_D2D1Scale, &scaleEffect);
	return scaleEffect;
}

ID2D1Effect* D2DGraphic::CreateScaleEffect(ID2D1Bitmap * bitmap)
{
	ID2D1Effect* scaleEffect;
	Context->CreateEffect(CLSID_D2D1Scale, &scaleEffect);

	scaleEffect->SetInput(0, bitmap);
	return scaleEffect;
}

ID2D1Effect* D2DGraphic::CreateScaleEffect(ID2D1Effect * imageEffect)
{
	ID2D1Effect* scaleEffect;
	Context->CreateEffect(CLSID_D2D1Scale, &scaleEffect);

	scaleEffect->SetInputEffect(0, imageEffect);
	return imageEffect;
}

void D2DGraphic::ScaleEffect(ID2D1Effect * Effect, D2D1_SIZE_F scaleSize, D2D1_POINT_2F centerPoint)
{
	//Effect->SetValue(D2D1_SCALE_PROP_INTERPOLATION_MODE, D2D1_SCALE_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR);
	Effect->SetValue(D2D1_SCALE_PROP_CENTER_POINT, centerPoint);
	Effect->SetValue(D2D1_SCALE_PROP_SCALE, scaleSize);
}

ID2D1Effect * D2DGraphic::CreateTintEffect()
{
	ID2D1Effect* tintEffect;
	Context->CreateEffect(CLSID_D2D1Tint, &tintEffect);
	return tintEffect;
}

ID2D1Effect* D2DGraphic::CreateTintEffect(ID2D1Bitmap * bitmap)
{
	ID2D1Effect* tintEffect;
	Context->CreateEffect(CLSID_D2D1Tint, &tintEffect);

	tintEffect->SetInput(0, bitmap);
	return tintEffect;
}

ID2D1Effect* D2DGraphic::CreateTintEffect(ID2D1Effect * imageEffect)
{
	ID2D1Effect* tintEffect;
	Context->CreateEffect(CLSID_D2D1Tint, &tintEffect);

	tintEffect->SetInputEffect(0, imageEffect);
	return tintEffect;
}

void D2DGraphic::TintEffect(ID2D1Effect * Effect, D2D1_VECTOR_4F color)
{
	Effect->SetValue(D2D1_TINT_PROP_COLOR, color);
}

ID2D1Effect * D2DGraphic::CreateTemperatureAndTintEffect()
{
	ID2D1Effect* temperatureAndTintEffect;
	Context->CreateEffect(CLSID_D2D1TemperatureTint, &temperatureAndTintEffect);
	return temperatureAndTintEffect;
}

ID2D1Effect* D2DGraphic::CreateTemperatureAndTintEffect(ID2D1Bitmap * bitmap)
{
	ID2D1Effect* temperatureAndTintEffect;
	Context->CreateEffect(CLSID_D2D1TemperatureTint, &temperatureAndTintEffect);

	temperatureAndTintEffect->SetInput(0, bitmap);

	return temperatureAndTintEffect;
}

ID2D1Effect* D2DGraphic::CreateTemperatureAndTintEffect(ID2D1Effect * imageEffect)
{
	ID2D1Effect* temperatureAndTintEffect;
	Context->CreateEffect(CLSID_D2D1TemperatureTint, &temperatureAndTintEffect);

	temperatureAndTintEffect->SetInputEffect(0, imageEffect);

	return temperatureAndTintEffect;
}

void D2DGraphic::TemperatureAndTintEffect(ID2D1Effect * Effect, float temperature, float tint)
{
	Effect->SetValue(D2D1_TEMPERATUREANDTINT_PROP_TEMPERATURE, temperature);
	Effect->SetValue(D2D1_TEMPERATUREANDTINT_PROP_TINT, tint);
}

ID2D1Effect * D2DGraphic::CreateSpotDiffuseLightingEffect()
{
	ID2D1Effect* spotDiffuseLightingEffect;
	Context->CreateEffect(CLSID_D2D1SpotSpecular, &spotDiffuseLightingEffect);

	return spotDiffuseLightingEffect;
}

ID2D1Effect * D2DGraphic::CreateSpotSpecularLightingEffect()
{
	ID2D1Effect* spotSpecularLightingEffect;
	Context->CreateEffect(CLSID_D2D1SpotSpecular, &spotSpecularLightingEffect);

	return spotSpecularLightingEffect;
}

ID2D1Effect* D2DGraphic::CreateSpotDiffuseLightingEffect(ID2D1Bitmap * bitmap)
{
	ID2D1Effect* spotDiffuseLightingEffect;

	Context->CreateEffect(CLSID_D2D1SpotSpecular, &spotDiffuseLightingEffect);
	spotDiffuseLightingEffect->SetInput(0, bitmap);

	return spotDiffuseLightingEffect;
}

void D2DGraphic::SpotDiffuseLightingEffect(ID2D1Effect* imageEffect, ID2D1Effect* alphaMask,D2D1_VECTOR_3F lightPoint , float angle, float focus ,float diffuse , D2D1_VECTOR_3F lightColor)
{
	//ID2D1Effect* alphaMask;
	ID2D1Image* image;
	ID2D1Image* outImage;


	imageEffect->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, lightPoint);
	imageEffect->SetValue(D2D1_SPOTDIFFUSE_PROP_LIMITING_CONE_ANGLE, angle);
	imageEffect->SetValue(D2D1_SPOTDIFFUSE_PROP_DIFFUSE_CONSTANT, diffuse);
	
	imageEffect->SetValue(D2D1_SPOTDIFFUSE_PROP_FOCUS, focus);
	imageEffect->SetValue(D2D1_SPOTDIFFUSE_PROP_COLOR, lightColor);
	imageEffect->SetValue(D2D1_SPOTDIFFUSE_PROP_SCALE_MODE, D2D1_SPOTDIFFUSE_SCALE_MODE_NEAREST_NEIGHBOR);

	imageEffect->GetInput(0, &image);
	imageEffect->GetOutput(&outImage);

	alphaMask->SetInput(1, outImage);
	alphaMask->SetInput(0, image);

	image->Release();
	outImage->Release();


	//Context->DrawImage(imageEffect, {100, 50});

}

void D2DGraphic::SpotSpecularLightingEffect(ID2D1Effect * imageEffect, ID2D1Effect * alphaMask, D2D1_VECTOR_3F lightPoint, float angle, float focus, float diffuse, D2D1_VECTOR_3F lightColor)
{
	ID2D1Image* image;
	ID2D1Image* outImage;


	imageEffect->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, lightPoint);
	imageEffect->SetValue(D2D1_SPOTDIFFUSE_PROP_LIMITING_CONE_ANGLE, angle);
	imageEffect->SetValue(D2D1_SPOTDIFFUSE_PROP_DIFFUSE_CONSTANT, diffuse);

	imageEffect->SetValue(D2D1_SPOTSPECULAR_PROP_FOCUS, focus);
	imageEffect->SetValue(D2D1_SPOTSPECULAR_PROP_COLOR, lightColor);
	imageEffect->SetValue(D2D1_SPOTSPECULAR_PROP_SCALE_MODE, D2D1_SPOTDIFFUSE_SCALE_MODE_NEAREST_NEIGHBOR);

	imageEffect->GetInput(0, &image);
	imageEffect->GetOutput(&outImage);

	alphaMask->SetInput(1, outImage);
	alphaMask->SetInput(0, image);

	image->Release();
	outImage->Release();

}

ID2D1Effect * D2DGraphic::CreateAlphaMaskEffect()
{
	ID2D1Effect* alphaMask;
	Context->CreateEffect(CLSID_D2D1AlphaMask, &alphaMask);
	return alphaMask;
}

ID2D1Effect * D2DGraphic::CreateContrastEffect()
{
	ID2D1Effect* contrastEffect;
	Context->CreateEffect(CLSID_D2D1Contrast, &contrastEffect);
	return contrastEffect;
}

void D2DGraphic::ContrastEffect(ID2D1Effect* imageEffect, float contrastValue, BOOL bvalue)
{
	imageEffect->SetValue(D2D1_CONTRAST_PROP_CONTRAST, contrastValue);
	imageEffect->SetValue(D2D1_CONTRAST_PROP_CLAMP_INPUT, bvalue);
}

void D2DGraphic::FontCreate(LPCWSTR fontName)
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(D2DWriteFactory), reinterpret_cast<IUnknown**>(&D2DWriteFactory));
	D2DWriteFactory->CreateTextFormat(
												fontName,									// ��Ʈ �йи� �̸��� ���ڿ�
												NULL,										// ��Ʈ �÷��� ��ü, NULL=�ý��� ��Ʈ �÷���
												DWRITE_FONT_WEIGHT_NORMAL,					// ��Ʈ ����. LIGHT, NORMAL, BOLD ��.
												DWRITE_FONT_STYLE_NORMAL,					// ��Ʈ ��Ÿ��. NORMAL, OBLIQUE, ITALIC.
												DWRITE_FONT_STRETCH_NORMAL,					// ��Ʈ ����. CONDENSED, NORMAL, MEDIUM, EXTEXDED ��.
												20,											// ��Ʈ ũ��.
												L"kr",										// �������� ���ڿ��� ���.  ����-�̱�=L"en-us", �ѱ���-�ѱ�=L"ko-kr"
												&textFormat);
	//pDWriteFactory->CreateBrus
	textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);            // ���� ���� ����
	textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);  // ���� ���� ����
	D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f), &textBrush);
}

void D2DGraphic::__DrawText(LPCWSTR wstring, D2D1_RECT_F rect)
{
	D2DRenderTarget->DrawTextA(wstring, static_cast<UINT32>(wcslen(wstring)), textFormat, rect, textBrush);
}
