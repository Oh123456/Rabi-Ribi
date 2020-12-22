#pragma once
#include "pch.h"
#include "Singleton.h"


#define D2DIE_ATLAS								0x001			//0b 0000 0000 0001
#define D2DIE_AFFINE							0x002			//0b 0000 0000 0010
#define D2DIE_SCALE								0x004			//0b 0000 0000 0100
#define D2DIE_TINT								0x008			//0b 0000 0000 1000
#define D2DIE_TEMPERATURE						0x010			//0b 0000 0001 0000
#define D2DIE_CONTRASTEFFECT					0x020			//0b 0000 0010 0000
#define D2DIE_SPOTSPECULARLIGHTING				0x200			//0b 0010 0000 0000
#define D2DIE_SPOTDIFFUSELIGHTING				0x400			//0b 0100 0000 0000
//#define IE_CHECK	0b1111111111

enum class EFFECTKIND : UINT
{
	BEGIN,
	ATLAS,
	SCALE,
	AFFINE,
	TINT,
	TEMPERATUREANDTINT,
	CONTRASTEFFECT,
	SPOTSPECULARLIGHTING,
	SPOTDIFFUSELIGHTING,
	ALPHAMASK,
	END
};

struct ScaleEffectInfo
{
	// ������ ������
	D2D1_SIZE_F scaleSize;
	// ������ ����Ʈ 
	D2D1_POINT_2F scaleCenterPoint = D2D1_POINT_2F();
};

struct SpotLightingEffectInfo
{
	D2D1_VECTOR_3F lightPoint = D2D1_VECTOR_3F();
	float angle = 90.0f;
	float focus = 1.0f;
	float diffuse = 1.0f;
	D2D1_VECTOR_3F lightColor = D2D1::Vector3F(1.0f, 1.0f, 1.0f);
};

struct TemperatureEffectInfo
{
	float temperature;
	float tint = 1.0f;
};

struct ContrastEffectInfo
{
	float contrast;
	BOOL clampInput = TRUE;
};

struct AtlasInfo
{
	// �������� ������
	D2D1_SIZE_U frameSize = D2D1_SIZE_U();
	// �� ������
	D2D1_POINT_2L frame = D2D1_POINT_2L();

	bool isCostumAtlas = false;
	D2D1_VECTOR_4F costumAtlasSize = D2D1_VECTOR_4F();
};

struct ImageInfo
{
	// �̹��� ��ǥ
	D2D1_POINT_2F imageLocation;
	// ��Ʋ�� ������
	AtlasInfo atlasInfo;
	// ���� ȿ�� ���
	D2D1_MATRIX_3X2_F affineMatrix = D2D1_MATRIX_3X2_F();
	// ������ ������
	ScaleEffectInfo scaleInfo;
	// ƾƮ ȿ�� ��
	D2D1_VECTOR_4F tintColor = D2D1_VECTOR_4F();
	// ���� ��ǻ�� ����Ʈ ����Ʈ 
	SpotLightingEffectInfo spotDiffuseInfo;
	// ���� ����ŧ�� ����Ʈ
	SpotLightingEffectInfo spotSpecularInfo;
	// �µ� �� ƾƮ ȿ�� 
	TemperatureEffectInfo temperatureInfo;
	// ��� ȿ�� 
	ContrastEffectInfo contrasteInfo;


	// �̹��� ����Ʈ �� IE_ATLAS
	UINT imageEffect = 0;
	// �̹��� �̸�
	LPCWCHAR imageName = L"";
};


class ImageManager :public Singleton<ImageManager>
{
	typedef Singleton<ImageManager> Super;
	typedef std::map <LPCWSTR, ID2D1Bitmap*> ImageMap;
	typedef std::map <LPCWSTR, ID2D1Bitmap*>::const_iterator const_ImageMapiterator;

	typedef std::map <EFFECTKIND, ID2D1Effect*> EffectMap;
	typedef std::map <EFFECTKIND, ID2D1Effect*>::const_iterator const_EffectMapiterator;
public:
	~ImageManager() { this->Release(); }
	void Init();
	void Release();
	ID2D1Effect* FindEffect(EFFECTKIND keyValue);
	void ImageRander(const ImageInfo& imageInfo);
	void LoadPng(LPCWSTR imageName);
	void LoadPng(LPCWSTR keyValue ,LPCWSTR imageName);
	ID2D1Bitmap* FindImage(LPCWSTR keyValue);
	void SetDefaultDirectory(LPCWSTR directory = L"Image");
private:
	ImageMap images;
	EffectMap effects;
	LPCWSTR defaultDirectory;

};

