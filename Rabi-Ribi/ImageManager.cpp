#include "ImageManager.h"
#include "D2DGraphic.h"



void ImageManager::Init()
{
	D2D* d2d = d2d->GetSingleton();
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::ATLAS, d2d->CreateAtlasEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::AFFINE, d2d->CreateAffineTransformEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::SCALE, d2d->CreateScaleEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::TINT, d2d->CreateTintEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::TEMPERATUREANDTINT, d2d->CreateTemperatureAndTintEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::SPOTDIFFUSELIGHTING, d2d->CreateSpotDiffuseLightingEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::SPOTSPECULARLIGHTING, d2d->CreateSpotSpecularLightingEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::ALPHAMASK, d2d->CreateAlphaMaskEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::CONTRASTEFFECT, d2d->CreateContrastEffect()));
	effects.insert(pair<EFFECTKIND, ID2D1Effect*>(EFFECTKIND::EXPOSUREEFFECT, d2d->CreateExposureEffect()));

	defaultDirectory = L"";
}

void ImageManager::Release()
{
	const_EffectMapiterator emapit;
	ID2D1Effect* effect;
	for (emapit = effects.begin(); emapit != effects.end() ;emapit++)
	{
		effect = emapit->second;
		if (effect != nullptr)
			effect->Release();
	}
	effects.clear();

	const_ImageMapiterator imapit;
	ID2D1Image* image;
	for (imapit = images.begin(); imapit != images.end(); imapit++)
	{
		image = imapit->second;
		if (image != nullptr)
			image->Release();
	}
	images.clear();
	Super::ReleaseSingleton();
}

ID2D1Effect* ImageManager::FindEffect(EFFECTKIND keyValue)
{
	const_EffectMapiterator key = effects.find(keyValue);
	if (key != effects.end())
	{
		return key->second;
	}
	return nullptr;
}

void ImageManager::ImageRander(const ImageInfo& imageInfo)
{
	const_ImageMapiterator imagekey = images.find(imageInfo.imageName);
	ID2D1Bitmap* bitmap;

	D2D* d2d = d2d->GetSingleton();
	if (imagekey == images.end())
	{
		//DEBUG_MASSAGE("이미지 렌더중 알맞는 키값의 이미지가 없습니다.\n");
		return;
	}

	bitmap = imagekey->second;

	this->ImageRander(bitmap,imageInfo);

}

void ImageManager::ImageRander(ID2D1Bitmap * image, const ImageInfo & imageInfo)
{
	if (imageInfo.imageEffect & D2DIE_NOIMAGE)
		return;
	UINT imageEffect = imageInfo.imageEffect;
	ID2D1Effect* oldeffect = nullptr;
	ID2D1Effect* effect = nullptr;
	ID2D1Bitmap* bitmap = image;

	D2D* d2d = d2d->GetSingleton();
	if (bitmap == nullptr)
	{
		//DEBUG_MASSAGE("이미지 렌더중 알맞는 키값의 이미지가 없습니다.\n");
		return;
	}

	D2D1_SIZE_F bitmapSize = bitmap->GetSize();
	D2D1_POINT_2F drawLocation = { imageInfo.imageLocation.x - bitmapSize.width / 2 ,imageInfo.imageLocation.y - bitmapSize.height / 2 };
	if (imageInfo.imageEffect == 0)
	{

		D2D1_RECT_F drawrc = { imageInfo.imageLocation.x - bitmapSize.width / 2 ,imageInfo.imageLocation.y - bitmapSize.height / 2,
								imageInfo.imageLocation.x + bitmapSize.width / 2, imageInfo.imageLocation.y + bitmapSize.height / 2 };
		if ((drawrc.right < 0.0f) | (drawrc.bottom < 0.0f) |
			(drawrc.left > (d2d->GetD2DRenderTarget()->GetPixelSize().width / CAMERA->GetZoom().x)) | (drawrc.top > d2d->GetD2DRenderTarget()->GetPixelSize().height / CAMERA->GetZoom().y))
			return;
		d2d->GetDeviceContext()->DrawBitmap(bitmap, drawrc);
		return;
	}
	EFFECTKIND effectKind = EFFECTKIND::BEGIN;
	for (UINT i = static_cast<UINT>(EFFECTKIND::BEGIN); i < static_cast<UINT>(EFFECTKIND::END); i++)
	{
		effectKind = static_cast<EFFECTKIND>(i);
		switch (effectKind)
		{
		case EFFECTKIND::ATLAS:
			if (imageEffect & D2DIE_ATLAS)
			{
				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("아틀라스 이펙트가 널값입니다.\n");
					break;
				}
				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);
				UINT32 framx = imageInfo.atlasInfo.frame.x;
				UINT32 framy = imageInfo.atlasInfo.frame.y;
				D2D1_SIZE_F size = imageInfo.atlasInfo.frameSize;


				D2D1_VECTOR_4F atlasSize;

				if (!imageInfo.atlasInfo.isCostumAtlas)
					atlasSize = { (float)size.width * framx , (float)size.height *  framy,
								  (float)size.width * (framx + 1) , (float)size.height * (framy + 1) };
				else
				{
					atlasSize = imageInfo.atlasInfo.costumAtlasSize;
					size = { (float)(atlasSize.z - atlasSize.x) , (float)(atlasSize.w - atlasSize.y) };
				}
				drawLocation = { imageInfo.imageLocation.x - size.width / 2 ,imageInfo.imageLocation.y - size.height / 2 };
				if (((drawLocation.x + size.width) < 0.0f) | ((drawLocation.y + size.height) < 0.0f) | 
					((drawLocation.x ) > d2d->GetD2DRenderTarget()->GetPixelSize().width / CAMERA->GetZoom().x) | ((drawLocation.y ) > d2d->GetD2DRenderTarget()->GetPixelSize().height / CAMERA->GetZoom().y))
					return;
				//atlasSize.z -= 0.5f;
				//atlasSize.w -= 0.5f;
				d2d->AtlasEffect(effect, atlasSize);
				oldeffect = effect;
				effect = nullptr;
			}
			break;
		case EFFECTKIND::AFFINE:
			if (imageEffect & D2DIE_AFFINE)
			{
				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("아핀 이펙트가 널값입니다.\n");
					break;
				}

				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);

				d2d->AffineTransformEffect(effect, imageInfo.affineMatrix);
				oldeffect = effect;
				effect = nullptr;
			}
			break;
		case EFFECTKIND::SCALE:
			if (imageEffect & D2DIE_SCALE)
			{

				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("스케일 이펙트가 널값입니다. \n");
					break;
				}

				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);

				d2d->ScaleEffect(effect, imageInfo.scaleInfo.scaleSize, imageInfo.scaleInfo.scaleCenterPoint);
				oldeffect = effect;
				effect = nullptr;
			}
			break;

		case EFFECTKIND::TINT:
			if (imageEffect & D2DIE_TINT)
			{
				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("틴트 이펙트가 널값입니다.\n");
					break;
				}

				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);

				d2d->TintEffect(effect, imageInfo.tintColor);
				oldeffect = effect;
				effect = nullptr;
			}

			break;
		case EFFECTKIND::TEMPERATUREANDTINT:
			if (imageEffect & D2DIE_TEMPERATURE)
			{
				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("온도 이펙트가 널값입니다.\n");
					break;
				}

				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);
				TemperatureEffectInfo temperatireinfo = imageInfo.temperatureInfo;
				d2d->TemperatureAndTintEffect(effect, temperatireinfo.temperature, temperatireinfo.tint);
				oldeffect = effect;
				effect = nullptr;
			}
			break;

		case EFFECTKIND::CONTRASTEFFECT:
			if (imageEffect & D2DIE_CONTRASTEFFECT)
			{
				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("대비 효과 이펙트가 널값입니다.\n");
					break;
				}

				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);
				ContrastEffectInfo contrastInfo = imageInfo.contrasteInfo;
				d2d->ContrastEffect(effect, contrastInfo.contrast, contrastInfo.clampInput);
				oldeffect = effect;
				effect = nullptr;
			}
			break;
		case EFFECTKIND::EXPOSUREEFFECT:
			if (imageEffect & D2DIE_EXPOSUREEFFECT)
			{
				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("노출 효과 이펙트가 널값입니다.\n");
					break;
				}

				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);
				d2d->ExposureEffect(effect, imageInfo.exposureEffectInfo);
				oldeffect = effect;
				effect = nullptr;
			}
			break;
		case EFFECTKIND::SPOTSPECULARLIGHTING:
			if (imageEffect & D2DIE_SPOTSPECULARLIGHTING)
			{
				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("스폿 스펙큘럼 이펙트가 널값입니다.\n");
					break;
				}

				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);
				ID2D1Effect* alpha = this->FindEffect(EFFECTKIND::ALPHAMASK);
				SpotLightingEffectInfo specularInfo = imageInfo.spotSpecularInfo;
				d2d->SpotSpecularLightingEffect(effect, alpha, specularInfo.lightPoint, specularInfo.angle, specularInfo.focus, specularInfo.diffuse, specularInfo.lightColor);
				oldeffect = alpha;
				effect = nullptr;
			}
			break;
		case EFFECTKIND::SPOTDIFFUSELIGHTING:
			if (imageEffect & D2DIE_SPOTDIFFUSELIGHTING)
			{
				effect = this->FindEffect(effectKind);
				if (effect == nullptr)
				{
					DEBUG_MASSAGE("스폿 디퓨져 이펙트가 널값입니다.\n");
					break;
				}

				if (oldeffect == nullptr)
					effect->SetInput(0, bitmap);
				else
					effect->SetInputEffect(0, oldeffect);
				ID2D1Effect* alpha = this->FindEffect(EFFECTKIND::ALPHAMASK);
				SpotLightingEffectInfo DuffuseInfo = imageInfo.spotDiffuseInfo;
				d2d->SpotSpecularLightingEffect(effect, alpha, DuffuseInfo.lightPoint, DuffuseInfo.angle, DuffuseInfo.focus, DuffuseInfo.diffuse, DuffuseInfo.lightColor);
				oldeffect = alpha;
				effect = nullptr;

			}
			break;

		}
	}
	d2d->GetDeviceContext()->DrawImage(oldeffect, drawLocation);
}

void ImageManager::LoadPng(LPCWSTR imageName)
{
	string defaultstr = DefaultDirectory;
	wstring wdefaultstr;// = DefaultDirectory;
	wdefaultstr.assign(defaultstr.begin(), defaultstr.end());
	wstring png = L".png";
	wstring imageFullName = imageName + png;
	imageFullName = wdefaultstr + defaultDirectory + imageFullName;

	//LPCWSTR imageFullName = wcscat((wchar_t*)(imageName),L"_png");
	ID2D1Bitmap* loadBitmap = D2D::GetSingleton()->LoadImage_Png(imageFullName.c_str());
	images.insert(pair<LPCWSTR, ID2D1Bitmap*>(imageName, loadBitmap));
}

void ImageManager::LoadPng(LPCWSTR keyValue, LPCWSTR imageName)
{
	if (images.find(keyValue) != images.end())
		return;
	string defaultstr = DefaultDirectory;
	wstring wdefaultstr;// = DefaultDirectory;
	wdefaultstr.assign(defaultstr.begin(), defaultstr.end());
	wstring png = L".png";
	wstring imageFullName = imageName + png;
	imageFullName = wdefaultstr + defaultDirectory + imageFullName;

	//LPCWSTR imageFullName = wcscat((wchar_t*)(imageName),L"_png");
	ID2D1Bitmap* loadBitmap = D2D::GetSingleton()->LoadImage_Png(imageFullName.c_str());
	images.insert(pair<LPCWSTR, ID2D1Bitmap*>(keyValue, loadBitmap));
}

ID2D1Bitmap* ImageManager::FindImage(LPCWSTR keyValue)
{
	const_ImageMapiterator c_it = images.find(keyValue);
	if (c_it != images.end())
		return c_it->second;
	return nullptr;
}

void ImageManager::SetDefaultDirectory(LPCWSTR directory)
{
	defaultDirectory = directory;
}

