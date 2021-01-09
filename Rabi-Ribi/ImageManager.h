#pragma once
#include "pch.h"
#include "Singleton.h"


#define D2DIE_ATLAS								0x001			//0b 0000 0000 0001
#define D2DIE_AFFINE							0x002			//0b 0000 0000 0010
#define D2DIE_SCALE								0x004			//0b 0000 0000 0100
#define D2DIE_TINT								0x008			//0b 0000 0000 1000
#define D2DIE_TEMPERATURE						0x010			//0b 0000 0001 0000
#define D2DIE_CONTRASTEFFECT					0x020			//0b 0000 0010 0000
#define D2DIE_EXPOSUREEFFECT					0x040			//0b 0000 0100 0000
#define D2DIE_SPOTSPECULARLIGHTING				0x200			//0b 0010 0000 0000
#define D2DIE_SPOTDIFFUSELIGHTING				0x400			//0b 0100 0000 0000
#define D2DIE_DEFAULT					(D2DIE_ATLAS | \
										 D2DIE_AFFINE)
#define D2DIE_NOIMAGE							0x8000

enum class EFFECTKIND : UINT
{
	BEGIN,
	ATLAS,
	SCALE,
	AFFINE,
	TINT,
	EXPOSUREEFFECT,
	TEMPERATUREANDTINT,
	CONTRASTEFFECT,
	SPOTSPECULARLIGHTING,
	SPOTDIFFUSELIGHTING,
	ALPHAMASK,
	END
};

struct ScaleEffectInfo
{
	// 스케일 사이즈
	D2D1_SIZE_F scaleSize;
	// 스케일 포인트 
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
	// 한프레임 사이즈
	D2D1_SIZE_F frameSize = D2D1_SIZE_F();
	// 현 프레임
	D2D1_POINT_2L frame = D2D1_POINT_2L();

	bool isCostumAtlas = false;
	D2D1_VECTOR_4F costumAtlasSize = D2D1_VECTOR_4F();
};

struct ImageInfo
{
	// 이미지 좌표
	D2D1_POINT_2F imageLocation;
	// 아틀라스 사이즈
	AtlasInfo atlasInfo;
	// 아핀 효과 행렬
	D2D1_MATRIX_3X2_F affineMatrix = Matrix3x2F::Identity();
	// 스케일 사이즈
	ScaleEffectInfo scaleInfo;
	// 틴트 효과 색
	D2D1_VECTOR_4F tintColor = D2D1_VECTOR_4F();
	// 스폿 디퓨저 라이트 이펙트 
	SpotLightingEffectInfo spotDiffuseInfo;
	// 스폿 스펙큘럼 라이트
	SpotLightingEffectInfo spotSpecularInfo;
	// 온도 와 틴트 효과 
	TemperatureEffectInfo temperatureInfo;
	// 대비 효과 
	ContrastEffectInfo contrasteInfo;

	// -2.0f ~ 2.0f
	float exposureEffectInfo = 0.0f;

	// 이미지 이펙트 값 IE_ATLAS
	UINT imageEffect = 0;
	// 이미지 이름
	LPCWCHAR imageName = L"";
};

// 이미지 이팩트 추가
inline void AddImageEffect(ImageInfo& imageInfo, UINT imageEffect)
{
	imageInfo.imageEffect |= imageEffect;
}

// 이미지 이팩트 제거
inline void RemoveImageEffect(ImageInfo& imageInfo, UINT imageEffect)
{
	// 비트값이 0일때 XOR 연산을 할시 1로 변화 하기에 비트값이 1일때 XOR 연산을 시켜준다.
	if (imageInfo.imageEffect & imageEffect)
		imageInfo.imageEffect ^= imageEffect;
}

inline bool CheckImageEffect(ImageInfo& imageInfo, UINT imageEffect)
{
	return (imageInfo.imageEffect & imageEffect);
}

class ImageManager :public Singleton<ImageManager>
{
	typedef Singleton<ImageManager> Super;
	typedef std::map <LPCWSTR, ID2D1Bitmap*> ImageMap;
	typedef std::map <LPCWSTR, ID2D1Bitmap*>::const_iterator const_ImageMapiterator;

	typedef std::map <EFFECTKIND, ID2D1Effect*> EffectMap;
	typedef std::map <EFFECTKIND, ID2D1Effect*>::const_iterator const_EffectMapiterator;
public:
	~ImageManager() { }
	void Init();
	void Release();
	ID2D1Effect* FindEffect(EFFECTKIND keyValue);
	void ImageRander(const ImageInfo& imageInfo);
	void ImageRander(ID2D1Bitmap* image ,const ImageInfo& imageInfo);
	void LoadPng(LPCWSTR imageName);
	void LoadPng(LPCWSTR keyValue ,LPCWSTR imageName);
	ID2D1Bitmap* FindImage(LPCWSTR keyValue);
	void SetDefaultDirectory(LPCWSTR directory = L"Image");
private:
	ImageMap images;
	EffectMap effects;
	LPCWSTR defaultDirectory;

};

