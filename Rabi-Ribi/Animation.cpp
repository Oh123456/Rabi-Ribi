#include "Animation.h"

Animation::Animation() :
	image(nullptr), endPlayIndex({ 0,0 }), nowplayIndex({0,0}), isPlaying(false), speed(0.0f)
{
	imageKey.clear();
}

Animation::~Animation()
{
	this->Release();
}

void Animation::Play(float speed)
{
	isPlaying = true;
	TIMERMANAGER->SetTimer(timer,this,&Animation::AnimationTimer, speed);
}

void Animation::Stop()
{
	isPlaying = false;
	TIMERMANAGER->DeleteTimer(timer);
}

bool Animation::IsPlaying()
{
	if (isPlaying)
		return true;
	return false;
}

bool Animation::IsEmpty()
{
	if (image)
		return false;
	return true;
}

void Animation::SetAnimSpeed(float speed)
{
	this->speed = speed;
}

float Animation::GetAnimSpeed()
{
	return speed;
}

void Animation::SetLoop(bool value)
{
	isLoop = value;
}

bool Animation::GetLoop()
{
	return isLoop;
}


void Animation::SetPlayingAnimIndex(D2D1_POINT_2L index)
{
	nowplayIndex = { 0,0 };
	endPlayIndex = index;
}

void Animation::SetPlayingAnimIndex(D2D1_POINT_2L startindex, D2D1_POINT_2L endindex)
{
	startPlayIndex = startindex;
	nowplayIndex = startindex;
	endPlayIndex = endindex;
}

void Animation::SetImageinfo(ImageInfo & imageinfo)
{
	this->imageInfo = imageinfo;
	image = IMAGEMANAGER->FindImage(this->imageInfo.imageName);
}

ImageInfo& Animation::GetImageinfo()
{
	return imageInfo;
}

void Animation::Release()
{
	imageKey.clear();
	SAFE_RELEASE(image)
}

void Animation::AnimationTimer()
{
	nowplayIndex.x++;
	if (nowplayIndex.x > endPlayIndex.x)
	{
		nowplayIndex.x = startPlayIndex.x;
		nowplayIndex.y++;
		if (nowplayIndex.y > endPlayIndex.y)
		{
			nowplayIndex.y = 0;
			if (!isLoop)
				TIMERMANAGER->DeleteTimer(timer);
		}
	}
}
