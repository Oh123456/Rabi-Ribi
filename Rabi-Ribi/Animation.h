#pragma once
#include "Object.h"


_INTERFACE IAnimation 
{
	// speed = 재생 속도 
	virtual void Play(float speed = 1.0f) = 0;
	virtual void Stop() = 0;
	virtual bool IsPlaying() = 0;
	virtual bool IsEmpty() = 0;
	virtual void SetAnimSpeed(float speed) = 0;
	virtual float GetAnimSpeed() = 0;
	virtual void SetLoop(bool value) = 0;
	virtual bool GetLoop() = 0;
	virtual void SetPlayingAnimIndex(D2D1_POINT_2L startindex , D2D1_POINT_2L endindex) = 0;
	virtual void SetPlayingAnimIndex(D2D1_POINT_2L index) = 0;
	virtual void SetImageinfo(ImageInfo& imageinfo) = 0;
	virtual ImageInfo& GetImageinfo() = 0;
	virtual void Release() = 0;
};

class Animation : public IAnimation
{
public:
	Animation();
	~Animation();


	void Play(float speed = 1.0f)												override;
	void Stop()																	override;
	bool IsPlaying()															override;
	bool IsEmpty()																override;
	void SetAnimSpeed(float speed)												override;
	float GetAnimSpeed()														override;
	void SetLoop(bool value)													override;
	bool GetLoop()																override;
	void SetPlayingAnimIndex(D2D1_POINT_2L index)								override;
	void SetPlayingAnimIndex(D2D1_POINT_2L startindex, D2D1_POINT_2L endindex)	override;
	void SetImageinfo(ImageInfo& imageinfo)										override;
	ImageInfo& GetImageinfo()													override;
	void Release()																override;

private:
	void AnimationTimer();
private:
	D2D1_POINT_2L startPlayIndex;
	D2D1_POINT_2L endPlayIndex;
	D2D1_POINT_2L nowplayIndex;
	wstring imageKey;
	ID2D1Bitmap* image;
	ImageInfo imageInfo;
	bool isPlaying;
	bool isLoop;
	float speed;

	TimerHandle timer;
};
