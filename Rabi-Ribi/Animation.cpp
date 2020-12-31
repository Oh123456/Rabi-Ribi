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
	isEnd = false;
	nowAnimIndex = startAnimIndex;
}

void Animation::Stop()
{
	TIMERMANAGER->DeleteTimer(time);
	isPlaying = false;
	isEnd = true;
}

bool Animation::IsPlaying()
{
	return isPlaying;
}

bool Animation::IsEnd()
{
	return isEnd;
}

const Index_2U & Animation::GetNowIndex()
{
	return nowAnimIndex;
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

void Animation::Setting(const Index_2U & startAnimIndex, const Index_2U & endAnimIndex, float speed, bool isLoop)
{
	this->startAnimIndex = startAnimIndex;
	this->endAnimIndex = endAnimIndex;
	this->loopAnimIndex = startAnimIndex;
	this->loopendAnimIndex = endAnimIndex;
	this->speed = speed;
	this->isLoop = isLoop;
}

void Animation::SettingLoopIndex(const Index_2U & startAnimIndex, const Index_2U & endAnimIndex)
{
	loopAnimIndex = startAnimIndex;
	loopendAnimIndex = endAnimIndex;
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
			{
				nowAnimIndex = loopAnimIndex;
				endAnimIndex = loopendAnimIndex;
			}
			else
			{
				nowAnimIndex = endAnimIndex;
				TIMERMANAGER->DeleteTimer(time);
				isEnd = true;
				//isPlaying = false;
			}
		}
	}
}
