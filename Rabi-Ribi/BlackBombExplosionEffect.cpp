#include "BlackBombExplosionEffect.h"

BlackBombExplosionEffect::BlackBombExplosionEffect()
{
	effectFrame = EffectFrame::Blue_Explosion_Frame;
}

BlackBombExplosionEffect::~BlackBombExplosionEffect()
{
}

void BlackBombExplosionEffect::Render(ImageInfo & imageInfo)
{
	Super::Render(imageInfo);
}

void BlackBombExplosionEffect::Update(ImageInfo & imageInfo)
{
	if (!explosionEffctImage.empty())
	{
		deque<ImageInfo>::const_iterator c_it = explosionEffctImage.begin();
		for (; c_it != explosionEffctImage.end(); c_it++)
		{
			ImageInfo image = *c_it;
			image.imageLocation = { imageInfo.imageLocation.x + image.imageLocation.x,imageInfo.imageLocation.y + image.imageLocation.y };
			IMAGEMANAGER->ImageRander(image);
		}
	}
}

void BlackBombExplosionEffect::Release(ImageInfo & imageInfo)
{
	Super::Release(imageInfo);
}
