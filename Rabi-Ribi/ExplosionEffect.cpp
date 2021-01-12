#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect() : 
	count(0), isOneTime(true) , createExplosinTime(0.0f), isEnd(false)
{
	explosionEffctImage.clear();
	TIMERMANAGER->SetTimer(explosionTimer,this,&ExplosionEffect::CreateExplosionImage , 0.05f);

}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::Render(ImageInfo& imageInfo)
{
	if (!explosionEffctImage.empty())
	{
		deque<ImageInfo>::const_iterator c_it = explosionEffctImage.begin();
		for (; c_it != explosionEffctImage.end(); c_it++)
			IMAGEMANAGER->ImageRander((*c_it));
		
	}
}

void ExplosionEffect::Update(ImageInfo& imageInfo)
{
	ownerImageInfo = imageInfo;
	if (!explosionEffctImage.empty())
	{
		bool isZero = false;
		for (int i = 0; (size_t)i < (explosionEffctImage.size()); i++)
		{
			explosionEffctImage[i].tintColor.w -= 0.02f;
			if (explosionEffctImage[i].tintColor.w <= 0.0f)
			{
				explosionEffctImage[i].tintColor.w = 0.0f;
				isZero = true;
			}
		}
		if (isZero)
			explosionEffctImage.pop_front();
		if (explosionEffctImage.empty())
			isEnd = true;
	}


}

void ExplosionEffect::Release(ImageInfo& imageInfo)
{
	explosionEffctImage.clear();
	TIMERMANAGER->DeleteTimer(explosionTimer);
}

void ExplosionEffect::CreateExplosionImage()
{
	Location LT = { ownerImageInfo.imageLocation.x - ownerImageInfo.atlasInfo.frameSize.width / 2.0f , 
					ownerImageInfo.imageLocation.y - ownerImageInfo.atlasInfo.frameSize.height / 2.0f };
	float width = ownerImageInfo.atlasInfo.frameSize.width;
	float height = ownerImageInfo.atlasInfo.frameSize.height;

	int rnad_X = (int)(rand() % (int)(width)) - (int)(width / 2.0f);
	int rnad_Y = (int)(rand() % (int)(height)) - (int)(height / 2.0f);



	ImageInfo newImageInfo;
	newImageInfo.imageName = L"effect_a";
	newImageInfo.imageEffect = D2DIE_DEFAULT | D2DIE_TINT | D2DIE_EXPOSUREEFFECT;
	if (rand() % 2)
	{
		DWORD effectValue = Cast<DWORD>(effectFrame);
		newImageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	}
	else
	{
		DWORD effectValue = Cast<DWORD>(EffectFrame::White_Explosion_Frame);
		newImageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
	}
	newImageInfo.tintColor = { 1.0f,1.0f,1.0f,1.0f };
	newImageInfo.atlasInfo.frameSize = { 31.0f,31.0f };
	newImageInfo.imageLocation = { (float)rnad_X,(float)rnad_Y };
	explosionEffctImage.push_back(newImageInfo);

	if (isOneTime)
	{
		ZeroMemory(&newImageInfo,sizeof(ImageInfo));
		newImageInfo.imageName = L"effect_a";
		newImageInfo.imageEffect = D2DIE_DEFAULT | D2DIE_TINT | D2DIE_EXPOSUREEFFECT;
		if (rand() % 2)
		{
			DWORD effectValue = Cast<DWORD>(effectFrame);
			newImageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
		}
		else
		{
			DWORD effectValue = Cast<DWORD>(EffectFrame::White_Explosion_Frame);
			newImageInfo.atlasInfo.frame = { HIWORD(effectValue), LOWORD(effectValue) };
		}
		newImageInfo.tintColor = { 1.0f,1.0f,1.0f,1.0f };
		newImageInfo.atlasInfo.frameSize = { 31.0f,31.0f };
		newImageInfo.imageLocation = ownerImageInfo.imageLocation;
		explosionEffctImage.push_back(newImageInfo);
		isOneTime = false;
	}

	createExplosinTime += TIMERMANAGER->GetTimeElapsed();
	if (createExplosinTime >= 0.5f)
	{
		createExplosinTime = 0.f;
		TIMERMANAGER->DeleteTimer(explosionTimer);
	}
}
