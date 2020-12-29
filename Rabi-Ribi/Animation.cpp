#include "Animation.h"

Animation::Animation() : isPlaying(false)
{
	
}

Animation::~Animation()
{
}

void Animation::Play()
{
	TIMERMANAGER->SetTimer(time, this, &Animation::NextIndex, speed);
	isPlaying = true;
	nowAnimIndex = startAnimIndex;
}

void Animation::Stop()
{
	TIMERMANAGER->DeleteTimer(time);
	isPlaying = false;
}

bool Animation::IsPlaying()
{
	return isPlaying;
}

bool Animation::IsRevers()
{
	return this->isRevers;
}

void Animation::Release()
{
	TIMERMANAGER->DeleteTimer(time);
}

void Animation::Render(ImageInfo* imageInfo)
{
	
	imageInfo->atlasInfo.frame = { nowAnimIndex.x, nowAnimIndex.y };
	IMAGEMANAGER->ImageRander(*imageInfo);
}

void Animation::Setting(const Index_2U & startAnimIndex, const Index_2U & endAnimIndex, float speed, bool isLoop , bool isRevers)
{
	this->startAnimIndex = startAnimIndex;
	this->endAnimIndex = endAnimIndex;
	this->speed = speed;
	this->isLoop = isLoop;
	this->isRevers = isRevers;
}

void Animation::NextIndex()
{
	nowAnimIndex.x++;
	if (nowAnimIndex.x > endAnimIndex.x)
	{
		nowAnimIndex.x = startAnimIndex.x;
		nowAnimIndex.y++;
		if (nowAnimIndex.y > endAnimIndex.y)
		{
			if (isLoop)
				nowAnimIndex.y = startAnimIndex.y;
			else
			{
				TIMERMANAGER->DeleteTimer(time);
				isPlaying = false;
			}
		}
	}
}
