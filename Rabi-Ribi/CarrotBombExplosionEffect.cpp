#include "CarrotBombExplosionEffect.h"

CarrotBombExplosionEffect::CarrotBombExplosionEffect()
{
}

CarrotBombExplosionEffect::~CarrotBombExplosionEffect()
{
}

void CarrotBombExplosionEffect::Render(ImageInfo& imageInfo)
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

void CarrotBombExplosionEffect::Update(ImageInfo & imageInfo)
{
	Super::Update(imageInfo);

}

void CarrotBombExplosionEffect::Release(ImageInfo & imageInfo)
{
	Super::Release(imageInfo);
}
